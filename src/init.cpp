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
#include "bencode.h"
#include "alert.hpp"

namespace libtorrent {
namespace node {

NAN_MODULE_INIT(Init) {

  SET_VAL(target, "BEncode", Nan::GetFunction(Nan::New<v8::FunctionTemplate>(BEncode)).ToLocalChecked());

  TorrentHandle::Init(target);
  TorrentInfo::Init(target);
  libtorrent::node::Session::Init(target);
  libtorrent::node::alert_types::InitAlertTypes(target);
}

}}
