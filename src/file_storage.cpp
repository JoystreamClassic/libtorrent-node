#include "file_storage.hpp"
#include "utils.hpp"

using namespace v8;

Nan::Persistent<Function> FileStorage::constructor;

NAN_MODULE_INIT(FileStorage::Init) {
  Local<FunctionTemplate> tpl = Nan::New<FunctionTemplate>(NewInstance);
  tpl->SetClassName(Nan::New("FileStorage").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  Nan::SetPrototypeMethod(tpl, "fileName", file_name);
  Nan::SetPrototypeMethod(tpl, "filePath", file_path);
  Nan::SetPrototypeMethod(tpl, "fileSize", file_size);
  Nan::SetPrototypeMethod(tpl, "fileOffset", file_offset);

  constructor.Reset(Nan::GetFunction(tpl).ToLocalChecked());
  Nan::Set(target, Nan::New("FileStorage").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());
}

Local<Object> FileStorage::New(libtorrent::file_storage fs) {
    Nan::EscapableHandleScope scope;

    Local<Function> cons = Nan::New(constructor);
    Nan::MaybeLocal<Object> obj = cons->NewInstance(Nan::GetCurrentContext());

    Nan::ObjectWrap::Unwrap<FileStorage>(obj.ToLocalChecked())->file_storage_ = fs;

    return scope.Escape(obj.ToLocalChecked());
}

NAN_METHOD(FileStorage::NewInstance) {
  if (!info.IsConstructCall()) {
    Nan::ThrowTypeError("Use the new operator to create instances of this object.");
    return;
  }

  FileStorage* obj = new FileStorage();
  obj->Wrap(info.This());

  RETURN(info.This());
};

NAN_METHOD(FileStorage::file_name) {
  REQUIRE_ARGUMENTS(1);

  uint32_t index;
  if (ARGUMENTS_IS_NUMBER(0)) {
    index = info[0]->IntegerValue();
  }

  std::string name = FileStorage::Unwrap(info.This())->file_name(index);

  RETURN(Nan::New<String>(name).ToLocalChecked());
};

NAN_METHOD(FileStorage::file_path) {
  REQUIRE_ARGUMENTS(1);

  uint32_t index;
  if (ARGUMENTS_IS_NUMBER(0)) {
    index = info[0]->IntegerValue();
  }

  std::string name = FileStorage::Unwrap(info.This())->file_name(index);

  RETURN(Nan::New<String>(name).ToLocalChecked());
};

NAN_METHOD(FileStorage::file_size) {
  REQUIRE_ARGUMENTS(1);

  uint32_t index;
  if (ARGUMENTS_IS_NUMBER(0)) {
    index = info[0]->IntegerValue();
  }

  std::string name = FileStorage::Unwrap(info.This())->file_name(index);

  RETURN(Nan::New<String>(name).ToLocalChecked());
};

NAN_METHOD(FileStorage::file_offset) {
  REQUIRE_ARGUMENTS(1);

  uint32_t index;
  if (ARGUMENTS_IS_NUMBER(0)) {
    index = info[0]->IntegerValue();
  }

  std::string name = FileStorage::Unwrap(info.This())->file_name(index);

  RETURN(Nan::New<String>(name).ToLocalChecked());
};
