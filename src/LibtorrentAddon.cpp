/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, January 25 2017
 */

#include "init.hpp"

NAN_MODULE_INIT(InitNativeExtension) {
  libtorrent::node::Init(target);
}

NODE_MODULE(LibtorrentAddon, InitNativeExtension)
