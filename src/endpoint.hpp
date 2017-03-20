/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, Januar 16 2017
 */

#ifndef LIBTORRENT_NODE_ENDPOINT_HPP
#define LIBTORRENT_NODE_ENDPOINT_HPP

#include <nan.h>
#include <libtorrent/socket.hpp> // cannot forward declare libtorrent::tcp::endpoint

namespace libtorrent {
namespace node {
namespace endpoint {

  /**
   * Endpoint is encoded as
   * {
   *  address : { see address for format },
   *  port : { Number }
   * }
   */

  v8::Local<v8::Object> encode(const libtorrent::tcp::endpoint & e);
  libtorrent::tcp::endpoint decode(const v8::Local<v8::Value> & o);

}}}

#endif // LIBTORRENT_NODE_ENDPOINT_HPP
