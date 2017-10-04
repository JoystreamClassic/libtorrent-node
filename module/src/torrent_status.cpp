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
#define TOTAL_DONE_KEY "totalDone"
#define TOTAL_DOWNLOAD_KEY "totalDownload"
#define TOTAL_UPLOAD_KEY "totalUpload"
#define DOWNLOAD_RATE_KEY "downloadRate"
#define UPLOAD_RATE_KEY "uploadRate"
#define UPLOADS_LIMIT_KEY "uploadsLimit"
#define NUM_CONNECTIONS_KEY "numConnections"
#define NUM_PIECES_KEY "numPieces"
#define NUM_SEEDS_KEY "numSeeds"
#define NUM_PEERS_KEY "numPeers"


namespace libtorrent {
namespace node {
namespace torrent_status {

v8::Local<v8::Object> encode(const libtorrent::torrent_status & ts) {
  v8::Local<v8::Object> o = Nan::New<v8::Object>();

  SET_VAL(o, INFO_HASH_KEY, sha1_hash::encode(ts.info_hash));
  SET_VAL(o, STATE_KEY, state_t::encode(ts.state));
  SET_NUMBER(o, PROGRESS_KEY, ts.progress);
  SET_NUMBER(o, TOTAL_DONE_KEY, ts.total_done);
  SET_NUMBER(o, TOTAL_DOWNLOAD_KEY, ts.total_download);
  SET_NUMBER(o, TOTAL_UPLOAD_KEY, ts.total_upload);
  SET_NUMBER(o, DOWNLOAD_RATE_KEY, ts.download_rate);
  SET_NUMBER(o, UPLOAD_RATE_KEY, ts.upload_rate);
  SET_NUMBER(o, UPLOADS_LIMIT_KEY, ts.uploads_limit);
  SET_NUMBER(o, NUM_CONNECTIONS_KEY, ts.num_connections);
  SET_NUMBER(o, NUM_PIECES_KEY, ts.num_pieces);
  SET_NUMBER(o, NUM_SEEDS_KEY, ts.num_seeds);
  SET_NUMBER(o, NUM_PEERS_KEY, ts.num_peers);

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

libtorrent::torrent_status decode(const v8::Local<v8::Object> & o) {

  throw std::runtime_error("Not yet implemented?");

}

}
}
}
