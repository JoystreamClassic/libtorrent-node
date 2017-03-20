/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, Januar 17 2017
 */

#include "address.hpp"
#include "utils.hpp"

#include <libtorrent/socket_io.hpp>

namespace libtorrent {
namespace node {
namespace address {

v8::Local<v8::String> encode(const libtorrent::address & a) {

    std::string addressString = libtorrent::print_address(a);
    return Nan::New<v8::String>(addressString).ToLocalChecked();
}

libtorrent::address decode(const v8::Local<v8::Value> & o) {

  std::string addressString = ToNative<std::string>(o);

  libtorrent::error_code ec;
  libtorrent::address a = libtorrent::address::from_string(addressString, ec);

  if(ec)
    throw std::runtime_error(ec.message());
  else
    return a;
}

}
}
}
