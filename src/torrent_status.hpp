/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, Januar 16 2017
 */

#ifndef LIBTORRENT_NODE_TORRENT_STATUS_HPP
#define LIBTORRENT_NODE_TORRENT_STATUS_HPP

#include <nan.h>
#include <libtorrent/torrent_status.hpp>

namespace libtorrent {
  struct torrent_status;

namespace node {
namespace torrent_status {

  // Something about symbols? ...export state_t....

  /**
   * Status is encoded as
   * {
   *  info_hash : { see info_hash for format },
   *  state : { Number },
   *  progress : { Number }
   * }
   */

 v8::Local<v8::Object> encode(const libtorrent::torrent_status & s);
 libtorrent::torrent_status decode(const v8::Local<v8::Object> & o);

}
}
}

#endif // LIBTORRENT_NODE_TORRENT_STATUS_HPP
