/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Lola Rigaut-Luczack <rllola80@gmail.com>, January 24 2017
 */

#include "error_code.hpp"
#include "utils.hpp"

namespace libtorrent {
namespace node {
namespace error_code {

v8::Local<v8::Object> encode(const libtorrent::error_code & a) {
  return Nan::New<v8::Object>();
}

libtorrent::error_code decode(const v8::Local<v8::Object> & o) {
  return libtorrent::error_code();
}

}
}
}
