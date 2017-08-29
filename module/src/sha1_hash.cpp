/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, Januar 16 2017
 */

#include "sha1_hash.hpp"
#include "utils.hpp"

namespace libtorrent {
namespace node {
namespace sha1_hash {

v8::Local<v8::String> encode(const libtorrent::sha1_hash & h) {
  return Nan::New(libtorrent::to_hex(h.to_string())).ToLocalChecked();
}

libtorrent::sha1_hash sha1FromHex(const std::string & hex) {

  if(hex.size() != 2*libtorrent::sha1_hash::size)
    throw std::runtime_error("incorrent length of hex string");

  char buf[libtorrent::sha1_hash::size];

  if(!libtorrent::from_hex(hex.c_str(), hex.size(), buf))
    throw std::runtime_error("invalid hex string");

  return libtorrent::sha1_hash(buf);
}

libtorrent::sha1_hash decode(const v8::Local<v8::Value> & o) {
  std::string hexString = ToNative<std::string>(o);
  return sha1FromHex(hexString);
}

}
}
}
