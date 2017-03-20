from conans import ConanFile, tools
import os
import subprocess
import shutil

class LibtorrentNodeConan(ConanFile):
    name = "LibtorrentNode"
    version = "1.1.1"
    license = "(c) JoyStream Inc. 2016-2017"
    url = "https://github.com/JoyStream/libtorrent-node.git"
    description = "Conan recipe for libtorrent-node library"
    source_url = "git@github.com:JoyStream/libtorrent-node.git"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    requires = "Libtorrent/1.1.1@joystream/stable"

    options = {
      "runtime": ["node", "electron"],
    }

    default_options = "runtime=node"

    def configure(self):
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

    def source(self):
        self.run("git clone %s" % self.source_url)
        self.run("cd libtorrent-node && git checkout master")

    def build(self):
        shutil.copy("conanbuildinfo.cmake", "libtorrent-node/")

        os.chdir('libtorrent-node')
        self.run('npm install cmake-js')
        self.run('npm install nan')

        #use self.settings to influence some cmake-js arguments
        debug = "--debug" if self.settings.build_type == "Debug" else ""

        # conan uses values x86 and x86_64 for 32bit and 64bit architecture, convert to cmake-js/node-gyp notation
        arch = ""
        if self.settings.arch == "x86_64":
            arch = "--arch=x64"
        elif self.settings.arch == "x86":
            arch == "--arch=ia32"
        else: arch = "--arch=%s" %self.settings.arch

        runtime = "--runtime=%s" % self.options.runtime

        #get runtime version from installed node/electron
        p = subprocess.Popen([str(self.options.runtime), "--version"], stdout=subprocess.PIPE)
        runtime_version = "--runtime-version=%s" % p.communicate()[0][1:]

        self.run('npm run compile -- %s %s %s %s' % (debug, arch, runtime, runtime_version))

    def package(self):
        self.copy("*.hpp", dst="include/libtorrent-node/", src="libtorrent-node/")
        self.copy("*.h", dst="include/libtorrent-node/", src="libtorrent-node/")
        self.copy("*.a", dst="lib", keep_path=False)
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.node", dst="addon", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["torrent_node_static"]
