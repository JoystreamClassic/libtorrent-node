#ifndef LIBTORRENT_NODE_TORRENT_INFO_HPP
#define LIBTORRENT_NODE_TORRENT_INFO_HPP

#include <nan.h>
#include <boost/optional.hpp>
#include <libtorrent/torrent_info.hpp>

using namespace v8;

class TorrentInfo: public Nan::ObjectWrap {
    public:
      static NAN_MODULE_INIT(Init);
      static Local<Object> New(boost::shared_ptr<const libtorrent::torrent_info> ti);
      static boost::shared_ptr<const libtorrent::torrent_info> Unwrap(const Local<Object>& obj) {
        TorrentInfo* ti = Nan::ObjectWrap::Unwrap<TorrentInfo>(obj);
        return ti->torrent_info_;
      };

    private:
      boost::shared_ptr<const libtorrent::torrent_info> torrent_info_;
      static Nan::Persistent<v8::Function> constructor;

      explicit TorrentInfo() {};
      explicit TorrentInfo(boost::shared_ptr<libtorrent::torrent_info> ti) : torrent_info_(ti) {};

      static NAN_METHOD(NewInstance);
      static NAN_METHOD(name);
      static NAN_METHOD(total_size);

};

#endif // LIBTORRENT_NODE_TORRENT_INFO_HPP
