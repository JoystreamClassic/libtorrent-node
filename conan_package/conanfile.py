import os
import shutil
from distutils.dir_util import copy_tree
from base import LibtorrentNodeBase


# The reason the local package is named conanfile.py and not testing.py is to we can run
# the test_pacakge command (it doesn't accept a --filename arg)
# This way the "default mode" of working with the pacakges is with the testing channels

# By default conan export uses the testing channel if not specified so it is also convenient to just run
# `conan export joystream` for local development

LOCAL_REPO_PATH_ENV = "LIBTORRENT_NODE_LOCAL_REPO_PATH"

class LibtorrentNodeTesting(LibtorrentNodeBase):
    # No real version is defined when working with a package on the testing channel
    # Keep at at 0.0.0 to detect accidentally exporting to stable branch
    # It would be nice to have a method that conan calls when the recipie is being exported
    version = "0.0.0"

    exports = "base.py"

    exports_sources = "../module*"

    # override base policy
    build_policy="always"

    def source(self):
        repo_path = os.getenv(LOCAL_REPO_PATH_ENV)

        if (repo_path):
            os.makedirs("repo/module")
            copy_tree("%s/module" % repo_path, "repo/module")
        else:
            os.mkdir("repo")
            shutil.move("module", "repo/")
