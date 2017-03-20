/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, Januar 16 2017
 */

#ifndef LIBTORRENT_NODE_INFO_HASH_HPP
#define LIBTORRENT_NODE_INFO_HASH_HPP

#include <nan.h>
#include <libtorrent/sha1_hash.hpp>

namespace libtorrent {
namespace node {
namespace sha1_hash {

  /**
   * Encoded as hex string.
   */

 v8::Local<v8::String> encode(const libtorrent::sha1_hash & h);
 libtorrent::sha1_hash decode(const v8::Local<v8::Value> & o);

}
}
}

#endif // LIBTORRENT_NODE_INFO_HASH_HPP
