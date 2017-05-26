/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, Januar 16 2017
 */

#ifndef LIBTORRENT_NODE_PEERID_HPP
#define LIBTORRENT_NODE_PEERID_HPP

#include <nan.h>
#include <libtorrent/peer_id.hpp>

namespace libtorrent {
namespace node {
namespace peer_id {

  /**
   * libtorrent::peer_id is encoded as a hex string
   */

  v8::Local<v8::String> encode(const libtorrent::peer_id & e);
  libtorrent::peer_id decode(const v8::Local<v8::Value> & o);

}}}

#endif // LIBTORRENT_NODE_PEERID_HPP
