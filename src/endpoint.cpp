/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, January 16 2017
 */

#include "endpoint.hpp"
#include "address.hpp"
#include "utils.hpp"

#define ADDRESS_KEY "address"
#define PORT_KEY "key"

namespace libtorrent {
namespace node {
namespace endpoint {

v8::Local<v8::Object> encode(const libtorrent::tcp::endpoint & ep) {

    v8::Local<v8::Object> o = Nan::New<v8::Object>();

    SET_VAL(o, ADDRESS_KEY, libtorrent::node::address::encode(ep.address()));
    SET_UINT32(o, PORT_KEY, ep.port());

    return o;
}

libtorrent::tcp::endpoint decode(const v8::Local<v8::Value> & v) {

  libtorrent::tcp::endpoint endpoint;

  if(!v->IsObject())
    throw std::runtime_error("Argument must be dictionary.");

  v8::Local<v8::Object> o = v->ToObject();

  v8::Local<v8::Value> addressValue = GET_VAL(o, ADDRESS_KEY);

  libtorrent::address a = address::decode(addressValue);
  uint32_t port = GET_UINT32(o, PORT_KEY);

  endpoint.address(a);
  endpoint.port(port);

  return endpoint;

}

}
}
}
