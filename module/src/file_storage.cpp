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
  Nan::SetPrototypeMethod(tpl, "pieceLength", piece_length);
  Nan::SetPrototypeMethod(tpl, "numFiles", num_files);

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
  } else {
    Nan::ThrowTypeError("Index is expected to be a number.");
    return;
  }

  std::string name = FileStorage::Unwrap(info.This())->file_name(index);

  RETURN(Nan::New<String>(name).ToLocalChecked());
};

NAN_METHOD(FileStorage::file_path) {
  REQUIRE_ARGUMENTS(1);

  uint32_t index;
  if (ARGUMENTS_IS_NUMBER(0)) {
    index = info[0]->IntegerValue();
  } else {
    Nan::ThrowTypeError("Index is expected to be a number.");
    return;
  }

  std::string path = FileStorage::Unwrap(info.This())->file_path(index);

  RETURN(Nan::New<String>(path).ToLocalChecked());
};

NAN_METHOD(FileStorage::file_size) {
  REQUIRE_ARGUMENTS(1);

  uint32_t index;
  if (ARGUMENTS_IS_NUMBER(0)) {
    index = info[0]->IntegerValue();
  } else {
    Nan::ThrowTypeError("Index is expected to be a number.");
    return;
  }

  boost::int64_t size = FileStorage::Unwrap(info.This())->file_size(index);

  RETURN(Nan::New<Number>(size));
};

NAN_METHOD(FileStorage::file_offset) {
  REQUIRE_ARGUMENTS(1);

  uint32_t index;
  if (ARGUMENTS_IS_NUMBER(0)) {
    index = info[0]->IntegerValue();
  } else {
    Nan::ThrowTypeError("Index is expected to be a number.");
    return;
  }

  boost::int64_t offset = FileStorage::Unwrap(info.This())->file_offset(index);

  RETURN(Nan::New<Number>(offset));
};

NAN_METHOD(FileStorage::piece_length) {

  int piece_length = FileStorage::Unwrap(info.This())->piece_length();

  RETURN(Nan::New<Number>(piece_length));
};

NAN_METHOD(FileStorage::num_files) {

  int num_files = FileStorage::Unwrap(info.This())->num_files();

  RETURN(Nan::New<Number>(num_files));
};
