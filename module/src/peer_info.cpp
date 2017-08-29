/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Lola Rigaut-Luczak <rllola80@gmail.com>, January 18 2017
 */

#include "peer_info.hpp"

#define IP_KEY "ip"

namespace libtorrent {
namespace node {
namespace peer_info {

v8::Local<v8::Object> encode(const libtorrent::peer_info & pi) {

    v8::Local<v8::Object> o = Nan::New<v8::Object>();

    SET_VAL(o, IP_KEY, endpoint::encode(pi.ip));

    return o;
}

}
}
}
