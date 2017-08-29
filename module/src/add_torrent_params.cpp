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
#define FLAGS_KEY "flags"

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
    //SET_STD_STRING(o, RESUME_DATA_KEY, std::string(atp.resume_data.begin(), atp.resume_data.end()));
    SET_INT32(o, UPLOAD_LIMIT_KEY, atp.upload_limit);
    SET_INT32(o, DOWNLOAD_LIMIT_KEY, atp.download_limit);
    SET_VAL(o, FLAGS_KEY, flags::encode(atp.flags));

    return o;
}

libtorrent::add_torrent_params decode(const v8::Local<v8::Value> & v) {
  libtorrent::add_torrent_params atp;

  if(!v->IsObject())
    throw std::runtime_error("Argument must be dictionary.");

  v8::Local<v8::Object> o = v->ToObject();

  if (HAS_KEY(o, TI_KEY)) {
    v8::Local<v8::Value> ti_value = GET_VAL(o, TI_KEY);
    if (!ti_value->IsUndefined()) {
      boost::shared_ptr<const libtorrent::torrent_info> torrent_info = TorrentInfo::Unwrap(ti_value->ToObject());
      atp.ti = boost::make_shared<libtorrent::torrent_info>(*torrent_info.get());
    }
  }

  if (HAS_KEY(o, NAME_KEY)) {
    atp.name =  GET_STD_STRING(o, NAME_KEY);
  }

  if (HAS_KEY(o, SAVE_PATH_KEY)) {
    atp.save_path =  GET_STD_STRING(o, SAVE_PATH_KEY);
  }

  if (HAS_KEY(o, INFO_HASH_KEY)) {
    atp.info_hash = libtorrent::node::sha1_hash::decode(GET_VAL(o, INFO_HASH_KEY));
  }

  if (HAS_KEY(o, URL_KEY)) {
    atp.url =  GET_STD_STRING(o, URL_KEY);
  }

  if (HAS_KEY(o, RESUME_DATA_KEY)) {
    auto begin = GET_BUFFER_BEGIN(o, RESUME_DATA_KEY);
    auto end = GET_BUFFER_END(o, RESUME_DATA_KEY);
    std::copy(begin, end, std::back_inserter(atp.resume_data));
  }

  atp.upload_limit =  GET_INT32(o, UPLOAD_LIMIT_KEY);

  atp.download_limit =  GET_INT32(o, DOWNLOAD_LIMIT_KEY);

  if (HAS_KEY(o, FLAGS_KEY)) {
    atp.flags = flags::decode(GET_VAL(o, FLAGS_KEY));
  }

  return atp;
}

namespace flags {
  v8::Local<v8::Object> encode(const boost::uint64_t &flags) {
    v8::Local<v8::Object> o = Nan::New<v8::Object>();

    SET_BOOL(o, "seed_mode", (bool)(flags & libtorrent::add_torrent_params::flags_t::flag_seed_mode));
    SET_BOOL(o, "override_resume_data", (bool)(flags & libtorrent::add_torrent_params::flags_t::flag_override_resume_data));
    SET_BOOL(o, "upload_mode", (bool)(flags & libtorrent::add_torrent_params::flags_t::flag_upload_mode));
    SET_BOOL(o, "share_mode", (bool)(flags & libtorrent::add_torrent_params::flags_t::flag_share_mode));
    SET_BOOL(o, "apply_ip_filter", (bool)(flags & libtorrent::add_torrent_params::flags_t::flag_apply_ip_filter));
    SET_BOOL(o, "paused", (bool)(flags & libtorrent::add_torrent_params::flags_t::flag_paused));
    SET_BOOL(o, "auto_managed", (bool)(flags & libtorrent::add_torrent_params::flags_t::flag_auto_managed));
    SET_BOOL(o, "duplicate_is_error", (bool)(flags & libtorrent::add_torrent_params::flags_t::flag_duplicate_is_error));
    SET_BOOL(o, "merge_resume_trackers", (bool)(flags & libtorrent::add_torrent_params::flags_t::flag_merge_resume_trackers));
    SET_BOOL(o, "update_subscribe", (bool)(flags & libtorrent::add_torrent_params::flags_t::flag_update_subscribe));
    SET_BOOL(o, "super_seeding", (bool)(flags & libtorrent::add_torrent_params::flags_t::flag_super_seeding));
    SET_BOOL(o, "sequential_download", (bool)(flags & libtorrent::add_torrent_params::flags_t::flag_sequential_download));
    SET_BOOL(o, "use_resume_save_path", (bool)(flags & libtorrent::add_torrent_params::flags_t::flag_use_resume_save_path));
    SET_BOOL(o, "pinned", (bool)(flags & libtorrent::add_torrent_params::flags_t::flag_pinned));
    SET_BOOL(o, "merge_resume_http_seeds", (bool)(flags & libtorrent::add_torrent_params::flags_t::flag_merge_resume_http_seeds));
    SET_BOOL(o, "stop_when_ready", (bool)(flags & libtorrent::add_torrent_params::flags_t::flag_stop_when_ready));

    return o;
  }

#define FLAG_IS_SET(o, flag) (HAS_KEY(o, #flag) && GET_BOOL(o, #flag))

  boost::uint64_t decode(const v8::Local<v8::Value> & v) {
    if(!v->IsObject())
      throw std::runtime_error("Argument must be dictionary.");

    v8::Local<v8::Object> o = v->ToObject();

    // initialize the with default flags set
    boost::uint64_t flags = libtorrent::add_torrent_params::flags_t::default_flags;

    // flags override the defaults
    if(FLAG_IS_SET(o, "seed_mode")) flags |= libtorrent::add_torrent_params::flags_t::flag_seed_mode;
    if(FLAG_IS_SET(o, "override_resume_data")) flags |= libtorrent::add_torrent_params::flags_t::flag_override_resume_data;
    if(FLAG_IS_SET(o, "upload_mode")) flags |= libtorrent::add_torrent_params::flags_t::flag_upload_mode;
    if(FLAG_IS_SET(o, "share_mode")) flags |= libtorrent::add_torrent_params::flags_t::flag_share_mode;
    if(FLAG_IS_SET(o, "apply_ip_filter")) flags |= libtorrent::add_torrent_params::flags_t::flag_apply_ip_filter;
    if(FLAG_IS_SET(o, "paused")) flags |= libtorrent::add_torrent_params::flags_t::flag_paused;
    if(FLAG_IS_SET(o, "auto_managed")) flags |= libtorrent::add_torrent_params::flags_t::flag_auto_managed;
    if(FLAG_IS_SET(o, "duplicate_is_error")) flags |= libtorrent::add_torrent_params::flags_t::flag_duplicate_is_error;
    if(FLAG_IS_SET(o, "merge_resume_trackers")) flags |= libtorrent::add_torrent_params::flags_t::flag_merge_resume_trackers;
    if(FLAG_IS_SET(o, "update_subscribe")) flags |= libtorrent::add_torrent_params::flags_t::flag_update_subscribe;
    if(FLAG_IS_SET(o, "super_seeding")) flags |= libtorrent::add_torrent_params::flags_t::flag_super_seeding;
    if(FLAG_IS_SET(o, "sequential_download")) flags |= libtorrent::add_torrent_params::flags_t::flag_sequential_download;
    if(FLAG_IS_SET(o, "use_resume_save_path")) flags |= libtorrent::add_torrent_params::flags_t::flag_use_resume_save_path;
    if(FLAG_IS_SET(o, "pinned")) flags |= libtorrent::add_torrent_params::flags_t::flag_pinned;
    if(FLAG_IS_SET(o, "merge_resume_http_seeds")) flags |= libtorrent::add_torrent_params::flags_t::flag_merge_resume_http_seeds;
    if(FLAG_IS_SET(o, "stop_when_ready")) flags |= libtorrent::add_torrent_params::flags_t::flag_stop_when_ready;

    return flags;
  }
}

}
}
}
