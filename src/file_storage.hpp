#ifndef LIBTORRENT_NODE_FILE_STORAGE_HPP
#define LIBTORRENT_NODE_FILE_STORAGE_HPP

#include <nan.h>
#include <libtorrent/file_storage.hpp>

using namespace v8;

class FileStorage: public Nan::ObjectWrap {
    public:
      static NAN_MODULE_INIT(Init);
      static Local<Object> New(libtorrent::file_storage fs);
      static libtorrent::file_storage*  Unwrap(const Local<Object>& obj) {
        FileStorage* fs = Nan::ObjectWrap::Unwrap<FileStorage>(obj);
        return &fs->file_storage_;
      };

    private:
      libtorrent::file_storage file_storage_;

      static Nan::Persistent<Function> constructor;

      static NAN_METHOD(NewInstance);
      static NAN_METHOD(file_name);
      static NAN_METHOD(file_path);
      static NAN_METHOD(file_size);
      static NAN_METHOD(file_offset);

};
#endif // LIBTORRENT_NODE_ERROR_CODE_HPP
