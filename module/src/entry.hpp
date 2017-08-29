/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Lola Rigaut-Luczack <rllola80@gmail.com>, January 24 2017
 */

#ifndef LIBTORRENT_NODE_ENTRY_HPP
#define LIBTORRENT_NODE_ENTRY_HPP

#include <nan.h>

namespace libtorrent {
  class entry;
  class bdecode_node;

namespace node {
namespace entry {

  v8::Local<v8::Object> encode(const libtorrent::entry & a);
  libtorrent::bdecode_node decode(const v8::Local<v8::Value> & o);

}}}

#endif // LIBTORRENT_NODE_ENTRY_HPP
