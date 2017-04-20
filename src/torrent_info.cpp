#include "torrent_info.h"
#include "utils.hpp"
#include <libtorrent/create_torrent.hpp>

Nan::Persistent<v8::Function> TorrentInfo::constructor;

NAN_MODULE_INIT(TorrentInfo::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NewInstance);
  tpl->SetClassName(Nan::New("TorrentInfo").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "name", name);
  Nan::SetPrototypeMethod(tpl, "totalSize", total_size);
  Nan::SetPrototypeMethod(tpl, "pieceLength", piece_length);
  Nan::SetPrototypeMethod(tpl, "numPieces", num_pieces);
  Nan::SetPrototypeMethod(tpl, "toBuffer", to_buffer);
  Nan::SetPrototypeMethod(tpl, "isValid", is_valid);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("TorrentInfo").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

Local<Object> TorrentInfo::New(boost::shared_ptr<const libtorrent::torrent_info> ti) {
    Nan::EscapableHandleScope scope;

    v8::Local<v8::Function> cons = Nan::New(constructor);
    Nan::MaybeLocal<v8::Object> obj = cons->NewInstance(Nan::GetCurrentContext());

    Nan::ObjectWrap::Unwrap<TorrentInfo>(obj.ToLocalChecked())->torrent_info_ = ti;

    return scope.Escape(obj.ToLocalChecked());
}

NAN_METHOD(TorrentInfo::NewInstance) {
  if (!info.IsConstructCall()) return;

  boost::shared_ptr<libtorrent::torrent_info> ti;
  libtorrent::error_code ec;
  TorrentInfo* obj;
  if (ARGUMENTS_IS(0)) {
    // create torrent info from .torrent file, given file path
    if (ARGUMENTS_IS_STRING(0)) {
      std::string filename(*Nan::Utf8String(info[0]));
      ti = boost::shared_ptr<libtorrent::torrent_info>(new libtorrent::torrent_info(filename, ec));
      obj = new TorrentInfo(ti);

    } else if (ARGUMENTS_IS_OBJECT(0)) {
      // create torrent info from bencoded metadata
      if(!info[0]->IsUint8Array()){
        return Nan::ThrowTypeError("Argument is not a node buffer");
      }

      auto length = ::node::Buffer::Length(info[0]);
      auto encoded = ::node::Buffer::Data(info[0]);

      libtorrent::bdecode_node data;
      libtorrent::error_code ec;

      libtorrent::bdecode(encoded, encoded + length, data, ec);

      if(ec) {
        return Nan::ThrowTypeError(ec.message().c_str());
      }

      obj = new TorrentInfo(boost::shared_ptr<libtorrent::torrent_info>(new libtorrent::torrent_info(data)));

    } else {
      return Nan::ThrowTypeError("Cannot construct TorrentInfo from supplied argument");
    }
  } else {
    obj = new TorrentInfo();
  }

  /* Wee need boost::system::error
  if (ec != boost::system::errc::success) {
    return Nan::ThrowError(ec.message().c_str());
  }*/

  obj->Wrap(info.This());
  info.GetReturnValue().Set(info.This());
}

NAN_METHOD(TorrentInfo::name) {

    info.GetReturnValue().Set(Nan::New<v8::String>(TorrentInfo::Unwrap(info.This())->name()).ToLocalChecked());
}

NAN_METHOD(TorrentInfo::total_size) {

    std::int64_t total_size = TorrentInfo::Unwrap(info.This())->total_size();

    info.GetReturnValue().Set(Nan::New<v8::Number>(total_size));
}

NAN_METHOD(TorrentInfo::piece_length) {

    int piece_length = TorrentInfo::Unwrap(info.This())->total_size();

    info.GetReturnValue().Set(Nan::New<v8::Number>(piece_length));
}

NAN_METHOD(TorrentInfo::num_pieces) {

    int num_pieces = TorrentInfo::Unwrap(info.This())->total_size();

    info.GetReturnValue().Set(Nan::New<v8::Number>(num_pieces));
}

NAN_METHOD(TorrentInfo::to_buffer) {
    auto ti = TorrentInfo::Unwrap(info.This());

    std::vector<char> encoded;

    libtorrent::create_torrent ct(*ti);

    auto data = ct.generate();

    if(data.type() != libtorrent::entry::undefined_t) {
        libtorrent::bencode(std::back_inserter(encoded), data);
    }

    auto buffer = Nan::NewBuffer(encoded.size()).ToLocalChecked();
    auto pbuf = ::node::Buffer::Data(buffer);
    std::copy(encoded.begin(), encoded.end(), pbuf);

    info.GetReturnValue().Set(buffer);
}

NAN_METHOD(TorrentInfo::is_valid) {
  auto ti = TorrentInfo::Unwrap(info.This());
  info.GetReturnValue().Set(ti->is_valid());
}
