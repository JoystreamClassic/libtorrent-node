#include "bencode.h"

#define REQUIRE_ARGUMENTS(n)                                                  \
  if (info.Length() < (n)) {                                                  \
    return Nan::ThrowTypeError("Expected " #n "arguments");                   \
}

#define ARGUMENTS_IS_BUFFER(i)                                                \
(info.Length() >= (i) && node::Buffer::HasInstance(info[i]))

int BufferToBDecodeNode(v8::Local<v8::Value> buffer, libtorrent::bdecode_node& bnode) {
  char const* start = node::Buffer::Data(buffer);
  char const* end = start + node::Buffer::Length(buffer);
  boost::system::error_code ec;

  if (libtorrent::bdecode(start, end, bnode, ec) != 0) {
    Nan::ThrowError(ec.message().c_str());
    return 1;
  }

  return 0;
}

NAN_METHOD(BEncode) {
  REQUIRE_ARGUMENTS(1);

  libtorrent::entry entry = libtorrent::node::entry::decode(info[0]->ToObject());
  std::vector<char> data;
  libtorrent::bencode(std::back_inserter(data), entry);

  Nan::MaybeLocal<v8::Object> buffer = Nan::CopyBuffer(&*data.begin(), data.size());
  info.GetReturnValue().Set(buffer.ToLocalChecked());
}

NAN_METHOD(BDecode) {
  if (!ARGUMENTS_IS_BUFFER(0)) {
    return Nan::ThrowTypeError("Argument 0 must be a Buffer");
  }

  libtorrent::bdecode_node node;
  if (BufferToBDecodeNode(info[0], node) != 0) return;

  libtorrent::entry entry;
  entry = node;
  info.GetReturnValue().Set(libtorrent::node::entry::encode(entry));
}
