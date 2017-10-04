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

namespace libtorrent {
namespace node {
namespace torrent_status {

v8::Local<v8::Object> encode(const libtorrent::torrent_status & ts) {
  v8::Local<v8::Object> o = Nan::New<v8::Object>();

  SET_VAL(o, "infoHash", sha1_hash::encode(ts.info_hash));
  SET_VAL(o, "state", state_t::encode(ts.state));
  SET_NUMBER(o, "progress", ts.progress);
  SET_NUMBER(o, "totalDone", ts.total_done);
  SET_NUMBER(o, "totalDownload", ts.total_download);
  SET_NUMBER(o, "totalUpload", ts.total_upload);
  SET_NUMBER(o, "downloadRate", ts.download_rate);
  SET_NUMBER(o, "uploadRate", ts.upload_rate);
  SET_NUMBER(o, "uploadsLimit", ts.uploads_limit);
  SET_NUMBER(o, "numConnections", ts.num_connections);
  SET_NUMBER(o, "numPieces", ts.num_pieces);
  SET_NUMBER(o, "numSeeds", ts.num_seeds);
  SET_NUMBER(o, "numPeers", ts.num_peers);
  SET_BOOL(o, "uploadMode", ts.upload_mode);
  SET_BOOL(o, "shareMode", ts.share_mode);
  SET_BOOL(o, "superSeeding", ts.super_seeding);
  SET_BOOL(o, "paused", ts.paused);
  SET_BOOL(o, "autoManaged", ts.auto_managed);
  SET_BOOL(o, "isSeeding", ts.is_seeding);
  SET_BOOL(o, "isFinished", ts.is_finished);
  SET_BOOL(o, "seedMode", ts.seed_mode);
  SET_BOOL(o, "isLoaded", ts.is_loaded);
  SET_BOOL(o, "stopWhenReady", ts.stop_when_ready);

  return o;
}

}
}
}
