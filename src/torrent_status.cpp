/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, Januar 16 2017
 */

#include "torrent_status.hpp"
#include "state_t.hpp"
#include "sha1_hash.hpp"
#include "utils.hpp"

#define INFO_HASH_KEY "infoHash"
#define STATE_KEY "state"
#define PROGRESS_KEY "progress"

namespace libtorrent {
namespace node {
namespace torrent_status {

v8::Local<v8::Object> encode(const libtorrent::torrent_status & ts) {
  v8::Local<v8::Object> o = Nan::New<v8::Object>();

  SET_VAL(o, INFO_HASH_KEY, sha1_hash::encode(ts.info_hash));
  SET_VAL(o, STATE_KEY, state_t::createValue(ts.state));
  SET_NUMBER(o, PROGRESS_KEY, ts.progress);

  return o;
}

libtorrent::torrent_status decode(const v8::Local<v8::Object> & o) {

  throw std::runtime_error("Not yet implemented?");

}

}
}
}
