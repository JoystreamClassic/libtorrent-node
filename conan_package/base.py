from conans import ConanFile, tools
import os
import subprocess
import shutil

class LibtorrentNodeBase(ConanFile):
    name = "LibtorrentNode"
    version = "0.0.5"
    license = "(c) JoyStream Inc. 2016-2017"
    url = "https://github.com/JoyStream/libtorrent-node.git"
    description = "Conan recipe for libtorrent-node library"
    repo_ssh_url = "git@github.com:JoyStream/libtorrent-node.git"
    repo_https_url = "https://github.com/JoyStream/libtorrent-node.git"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    requires = "Libtorrent/1.1.1@joystream/stable"
    build_policy = "missing"

    options = {
      "runtime": ["node", "electron"],
      "runtime_version": "ANY"
    }

    def configure(self):
        if self.options.runtime_version == "":
          raise ValueError('Invalid runtime_version value')

        # build static libs
        self.options["Libtorrent"].deprecated_functions=False
        self.options["Libtorrent"].shared=False
        self.options["Boost"].shared=False
        self.options["zlib"].shared=False
        self.options["bzip2"].shared=False
        self.options["OpenSSL"].shared=False

        # with position independent code
        if self.settings.compiler != "Visual Studio":
          self.options["Libtorrent"].fPIC=True
          self.options["Boost"].fPIC=True
          self.options["bzip2"].fPIC=True

    def build(self):
        shutil.copy("conanbuildinfo.cmake", "repo/module/")

        os.chdir('repo/module')
        self.run('npm install cmake-js')
        self.run('npm install nan')

        #use self.settings to influence some cmake-js arguments
        debug = "--debug" if self.settings.build_type == "Debug" else ""

        # static MSVC++ runtime - custom definition which cmake-js will pass onto cmake as -DMSVC_RUNTIME
        msvc_runtime = "--CDMSVC_RUNTIME=static" if (self.settings.compiler == "Visual Studio" and self.settings.compiler.runtime == "MT") else ""

        # conan uses values x86 and x86_64 for 32bit and 64bit architecture, convert to cmake-js/node-gyp notation
        arch = ""
        if self.settings.arch == "x86_64":
            arch = "--arch=x64"
        elif self.settings.arch == "x86":
            arch = "--arch=ia32"
        else: arch = "--arch=%s" %self.settings.arch

        runtime = "--runtime=%s" % self.options.runtime
        runtime_version = "--runtime-version=%s" % self.options.runtime_version

        # We run cmake-js compile step directly, skipping node-gyp build system because we want to use the
        # conan dependencies of the project consuming the conan package. node-gyp build system is only used
        # when libtorrent-node is being built as a standalone npm package
        self.run('npm run cmake-js -- compile %s %s %s %s %s' % (debug, arch, runtime, runtime_version, msvc_runtime))

    def package(self):
        self.copy("*.hpp", dst="include/libtorrent-node/", src="repo/module/src/")
        self.copy("*.h", dst="include/libtorrent-node/", src="repo/module/src/")
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.node", dst="addon", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["torrent_node_static"]
