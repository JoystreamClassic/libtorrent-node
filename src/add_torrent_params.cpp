/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Lola Rigaut-Luczak <rllola80@gmail.com>, January 18 2017
 */

#include "add_torrent_params.hpp"
#include "torrent_info.h"
#include "sha1_hash.hpp"
#include "utils.hpp"

#define TI_KEY "ti"
#define NAME_KEY "name"
#define SAVE_PATH_KEY "savePath"
#define INFO_HASH_KEY "infoHash"
#define URL_KEY "url"
#define RESUME_DATA_KEY "resumeData"
#define UPLOAD_LIMIT_KEY "uploadLimit"
#define DOWNLOAD_LIMIT_KEY "downloadLimit"

#include <libtorrent/add_torrent_params.hpp>
#include <boost/make_shared.hpp>

namespace libtorrent {
namespace node {
namespace add_torrent_params {

v8::Local<v8::Object> encode(const libtorrent::add_torrent_params & atp) {

    v8::Local<v8::Object> o = Nan::New<v8::Object>();

    if (atp.ti) {
      SET_VAL(o, TI_KEY, TorrentInfo::New(boost::make_shared<const libtorrent::torrent_info>(*atp.ti.get())));
    }

    SET_STD_STRING(o, NAME_KEY, atp.name);
    SET_STD_STRING(o, SAVE_PATH_KEY, atp.save_path);
    SET_VAL(o, INFO_HASH_KEY, libtorrent::node::sha1_hash::encode(atp.info_hash));
    SET_STD_STRING(o, URL_KEY, atp.url);
    SET_STD_STRING(o, RESUME_DATA_KEY, std::string(atp.resume_data.begin(), atp.resume_data.end()));
    SET_INT32(o, UPLOAD_LIMIT_KEY, atp.upload_limit);
    SET_INT32(o, DOWNLOAD_LIMIT_KEY, atp.download_limit);

    return o;
}

libtorrent::add_torrent_params decode(const v8::Local<v8::Value> & v) {
  libtorrent::add_torrent_params atp;

  if(!v->IsObject())
    throw std::runtime_error("Argument must be dictionary.");

  v8::Local<v8::Object> o = v->ToObject();

  try {
    v8::Local<v8::Value> ti_value = GET_VAL(o, TI_KEY);
    if (!ti_value->IsUndefined()) {
      boost::shared_ptr<const libtorrent::torrent_info> torrent_info = TorrentInfo::Unwrap(ti_value->ToObject());
      atp.ti = boost::make_shared<libtorrent::torrent_info>(*torrent_info.get());
    }
  } catch(const std::runtime_error &) { }

  try {
    if (HAS_KEY(o, NAME_KEY)) {
      atp.name =  GET_STD_STRING(o, NAME_KEY);
    }
  } catch(const std::runtime_error &) { }

  try {
    if (HAS_KEY(o, SAVE_PATH_KEY)) {
      atp.save_path =  GET_STD_STRING(o, SAVE_PATH_KEY);
    }
  } catch(const std::runtime_error &) { }

  try {
    atp.info_hash = libtorrent::node::sha1_hash::decode(GET_VAL(o, INFO_HASH_KEY));
  } catch(const std::runtime_error &) { }

  try {
    if (HAS_KEY(o, URL_KEY)) {
      atp.url =  GET_STD_STRING(o, URL_KEY);
    }
  } catch(const std::runtime_error &) { }

  try {
    if (HAS_KEY(o, RESUME_DATA_KEY)) {
      std::string str = GET_STD_STRING(o, RESUME_DATA_KEY);
      std::copy(str.begin(), str.end(), std::back_inserter(atp.resume_data));
    }
  } catch(const std::runtime_error &) { }

  try {
    atp.upload_limit =  GET_INT32(o, UPLOAD_LIMIT_KEY);
  } catch(const std::runtime_error &) { }

  try {
    atp.download_limit =  GET_INT32(o, DOWNLOAD_LIMIT_KEY);
  } catch(const std::runtime_error &) { }

  return atp;
}

}
}
}
