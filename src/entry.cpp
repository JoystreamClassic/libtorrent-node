/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Lola Rigaut-Luczack <rllola80@gmail.com>, January 24 2017
 */

#include "entry.hpp"
#include "utils.hpp"

#include <libtorrent/entry.hpp>

#define ENTRY_KEY "entry"

namespace libtorrent {
namespace node {
namespace entry {

v8::Local<v8::Object> encode(const libtorrent::entry & e) {

  v8::Local<v8::Object> o = Nan::New<v8::Object>();

  SET_STD_STRING(o, ENTRY_KEY, e.to_string());

  return o;
}

libtorrent::entry decode(const v8::Local<v8::Object> & o) {
  libtorrent::entry e;

  // TODO
  //auto v = GET_VAL(o, ENTRY_KEY);

  return e;
}

}
}
}
