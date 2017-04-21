/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Lola Rigaut-Luczack <rllola80@gmail.com>, January 24 2017
 */

#include "entry.hpp"
#include "utils.hpp"

#include <libtorrent/entry.hpp>
#include <libtorrent/bencode.hpp>
#include <libtorrent/bdecode.hpp>

namespace libtorrent {
namespace node {
namespace entry {

v8::Local<v8::Object> encode(const libtorrent::entry & e) {

  std::vector<char> encoded;

  if(e.type() != libtorrent::entry::undefined_t) {
      libtorrent::bencode(std::back_inserter(encoded), e);
  }

  auto buffer = Nan::NewBuffer(encoded.size()).ToLocalChecked();
  auto pbuf = ::node::Buffer::Data(buffer);
  std::copy(encoded.begin(), encoded.end(), pbuf);

  return buffer;
}

libtorrent::bdecode_node decode(const v8::Local<v8::Value> & o) {
  if(!o->IsUint8Array()){
    throw std::runtime_error("object not a node buffer");
  }

  auto length = ::node::Buffer::Length(o);
  auto encoded = ::node::Buffer::Data(o);

  libtorrent::bdecode_node entry;
  libtorrent::error_code ec;

  libtorrent::bdecode(encoded, encoded + length, entry, ec);

  if(ec) {
    throw std::runtime_error(ec.message().c_str());
  }

  return entry;
}

}
}
}
