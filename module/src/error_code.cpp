/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Lola Rigaut-Luczak <rllola80@gmail.com>, January 24 2017
 */

#include "error_code.hpp"
#include "utils.hpp"

namespace libtorrent {
namespace node {
namespace error_code {

v8::Local<v8::Object> encode(const libtorrent::error_code & err) {
  auto o = Nan::New<v8::Object>();
  SET_STD_STRING(o, "message", err.message());
  SET_NUMBER(o, "value", err.value());
  return o;
}

}
}
}
