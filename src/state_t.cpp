/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Lola Rigaut-Luczack <rllola80@gmail.com>, January 19 2017
 */

#include "state_t.hpp"
#include "utils.hpp"

#include <stdexcept>

namespace libtorrent {
namespace node {
namespace state_t {

  #define SET_STATE_T(o, name) SET_VAL(o, #name, createValue(libtorrent::torrent_status::state_t::name));

  NAN_MODULE_INIT(Init) {

    v8::Local<v8::Object> object = Nan::New<v8::Object>();

    SET_STATE_T(object, unused_enum_for_backwards_compatibility);
    SET_STATE_T(object, checking_files);
    SET_STATE_T(object, downloading_metadata);
    SET_STATE_T(object, downloading);
    SET_STATE_T(object, finished);
    SET_STATE_T(object, seeding);
    SET_STATE_T(object, allocating);
    SET_STATE_T(object, checking_resume_data);

    SET_VAL(target, "TorrentState", object);
  }

  v8::Local<v8::Value> createValue(libtorrent::torrent_status::state_t state) {

    switch(state) {
      case libtorrent::torrent_status::state_t::unused_enum_for_backwards_compatibility: return Nan::New(0);
      case libtorrent::torrent_status::state_t::checking_files: return Nan::New(1);
      case libtorrent::torrent_status::state_t::downloading_metadata: return Nan::New(2);
      case libtorrent::torrent_status::state_t::downloading: return Nan::New(3);
      case libtorrent::torrent_status::state_t::finished: return Nan::New(4);
      case libtorrent::torrent_status::state_t::seeding: return Nan::New(5);
      case libtorrent::torrent_status::state_t::allocating: return Nan::New(6);
      case libtorrent::torrent_status::state_t::checking_resume_data: return Nan::New(7);
      default:
        assert(false);
    }

  }

  libtorrent::torrent_status::state_t fromValue(const v8::Local<v8::Value> & v) {

    uint32_t value = ToNative<uint32_t>(v);

    switch(value) {
      case 0: return libtorrent::torrent_status::state_t::unused_enum_for_backwards_compatibility;
      case 1: return libtorrent::torrent_status::state_t::checking_files;
      case 2: return libtorrent::torrent_status::state_t::downloading_metadata;
      case 3: return libtorrent::torrent_status::state_t::downloading;
      case 4: return libtorrent::torrent_status::state_t::finished;
      case 5: return libtorrent::torrent_status::state_t::seeding;
      case 6: return libtorrent::torrent_status::state_t::allocating;
      case 7: return libtorrent::torrent_status::state_t::checking_resume_data;
      default:
        throw std::runtime_error("Could not decode torrent_status::state_t: invalid encoding value");

    }

  }

}
}
}
