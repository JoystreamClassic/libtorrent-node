from conans import ConanFile
import os
import shutil

channel = os.getenv("CONAN_CHANNEL", "stable")
username = os.getenv("CONAN_USERNAME", "joystream")


class LibtorrentNodeTestConan(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    requires = "LibtorrentNode/1.1.1@%s/%s" % (username, channel)

    options = {
      "runtime": ["node", "electron"],
      "runtime_version": "ANY"
    }

    def configure(self):
      self.options["LibtorrentNode"].runtime=self.options.runtime
      self.options["LibtorrentNode"].runtime_version=self.options.runtime_version

    def build(self):
      # copy test.js from test_package/ to the build directory
      test_js = str('%s%stest.js' % (self.conanfile_directory, os.sep))
      shutil.copy(test_js, ".")

    def imports(self):
      self.copy("*.node", src="addon", dst=".")

    def test(self):
        if self.options.runtime == 'electron':
          self.run('electron test.js')
        else:
          self.run("node test.js")
