var fs = require('fs-extra')
var rimraf = require('rimraf')
var BuildSystem = require('cmake-js').BuildSystem
var spawn = require('child_process').spawn
var minimist = require('minimist')

// Use a custom build folder for cmake-js to avoid conflict with node-gyp
var CMAKEJS_BUILD_DIR = 'build-cmakejs'

if(process.platform === 'win32') {
  process.chdir('../');
}

function clean() {
    try {
        fs.unlinkSync('./conaninfo.txt')
        fs.unlinkSync('./conanbuildinfo.cmake')
        rimraf.sync(CMAKEJS_BUILD_DIR)
    } catch(e){}
}

function getRuntimeAndVersion() {
    return new Promise(function(resolve, reject){
        var options = minimist(process.argv.slice(2),{boolean:true});

        if(!options.nodedir) {
          return reject(new Error('use node-gyp to build'))
        }

        // building for node runtime unless iojs appears in the nodedir path
        // which indicates using dev headers for electron
        options.runtime = options.nodedir.indexOf('iojs') === -1 ? 'node' : 'electron'

        if(!options.target) {
          if(options.runtime !== 'node') {
            // if buliding for electron target (runtime version must be provided)
            return reject(new Error('target not specified'))
          }

          options.runtime_version = process.versions.node
        } else {
          options.runtime_version = options.target
        }

        if(!options.arch) {
          if(options.runtime !== 'node') {
            // if building for electron architecture must be specified
            return reject(new Error('arch not specified'))
          }

          options.arch = process.arch
        }

        options.debug = process.env.BUILDTYPE === 'Debug'

        resolve(options)
    })
}

function conanInstall(options) {
    console.log('conan install with options:', options)

    // node-gyp sets MAKEFLAGS env var that looks like: "r -- BUILDTYPE=Release"
    // -r make flags is causing build issue for openssl and zlib on OSX
    // BUILDTYPE=Debug/Release is redundant (it is set in BUILDTYPE env var)
    // so just clearing the flag here
    process.env.MAKEFLAGS=''

    var args = ['install', '.', '--build=missing']
    args.push("-oruntime=" + options.runtime)
    args.push("-oruntime_version=" + options.runtime_version)

    if (process.platform === 'win32') {
        args.push("-scompiler=Visual Studio")
        args.push("-scompiler.runtime=MT")
    }

    var mapping = {
        'x64' : 'x86_64',
        'ia32' : 'x86'
    }

    //conan architecture setting
    if(options.arch) {
        args.push("-sarch=" + (mapping[options.arch] || options.arch))
    }

    if(options.debug) {
        args.push("-sbuild_type=Debug")
    }

    return new Promise(function(resolve, reject){
        var child = spawn('conan', args, {stdio: 'inherit', detached:false})

        child.on('close', function(exit_code){
            if(exit_code === 0) return resolve(options)

            reject()
        })
    })
}

function rebuild(opts){
    var mapping = {
        'x86_64' : 'x64',
        'x86' : 'ia32'
    }

    var options = {
        runtime: opts.runtime,
        runtimeVersion: opts.runtime_version,
        arch: mapping[opts.arch] || opts.arch,
        debug: opts.debug,
        out: CMAKEJS_BUILD_DIR
    }

    console.log('cmake-js rebuild with options:', options)

    // configure build system
    var bs = new BuildSystem(options)

    // rebuild() the addon instead of just compile(), to avoid issues when switching runtimes
    return bs.rebuild().then(function(){
        // copy module from custom build location to build/ folder
        if(process.platform == 'win32') {
          // on windows with visual studio, .node files is produced in different locaiton
          fs.copySync('build-cmakejs/bin/LibtorrentAddon.node', 'build/LibtorrentAddon.node')
        } else {
          fs.copySync('build-cmakejs/build-cmakejs/' + process.env.BUILDTYPE + '/LibtorrentAddon.node', 'build/LibtorrentAddon.node')
        }
    })
}

clean()
getRuntimeAndVersion()
  .then(conanInstall)
  .then(rebuild)
  .catch(function(err){
    console.error('LibtorrentAddon build failed:', err)
    process.exit(-1)
  })
