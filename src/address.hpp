/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, January 17 2017
 */

#ifndef LIBTORRENT_NODE_ADDRESS_HPP
#define LIBTORRENT_NODE_ADDRESS_HPP

#include <nan.h>
#include <libtorrent/address.hpp> // cannot forward declare libtorrent::address

namespace libtorrent {
namespace node {
namespace address {

  // Address is encoded as a string in dotted decimal format.

  v8::Local<v8::String> encode(const libtorrent::address & a);
  libtorrent::address decode(const v8::Local<v8::Value> & o);

}}}

#endif // LIBTORRENT_NODE_ADDRESS_HPP
