#ifndef LIBTORRENT_NODE_BENCODE_HPP
#define LIBTORRENT_NODE_BENCODE_HPP

#include <nan.h>
#include <libtorrent/bencode.hpp>
#include <libtorrent/bdecode.hpp>

#include "entry.hpp"

int BufferToBDecodeNode(v8::Local<v8::Value>, libtorrent::bdecode_node&);

NAN_METHOD(BEncode);
NAN_METHOD(BDecode);

#endif // LIBTORRENT_NODE_BENCODE_HPP
