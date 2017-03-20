#include "torrent_info.h"
#include "utils.hpp"

Nan::Persistent<v8::Function> TorrentInfo::constructor;

NAN_MODULE_INIT(TorrentInfo::Init) {
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(NewInstance);
  tpl->SetClassName(Nan::New("TorrentInfo").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "name", name);
  Nan::SetPrototypeMethod(tpl, "totalSize", total_size);

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
    if (ARGUMENTS_IS_STRING(0)) {
      std::string filename(*Nan::Utf8String(info[0]));
      ti = boost::shared_ptr<libtorrent::torrent_info>(new libtorrent::torrent_info(filename, ec));
      obj = new TorrentInfo(ti);
    } else {
      return Nan::ThrowTypeError("Arguments must be String");
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
