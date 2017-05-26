/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, January 25 2017
 */

#include "init.hpp"
#include "session.hpp"
#include "torrent_handle.h"
#include "torrent_info.h"
#include "alert.hpp"
#include "state_t.hpp"

namespace libtorrent {
namespace node {

NAN_MODULE_INIT(Init) {
  TorrentHandle::Init(target);
  TorrentInfo::Init(target);
  libtorrent::node::Session::Init(target);
  libtorrent::node::alert_types::InitAlertTypes(target);
  state_t::Init(target);
}

}}
