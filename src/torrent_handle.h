#ifndef LIBTORRENT_NODE_TORRENT_HANDLE_HPP
#define LIBTORRENT_NODE_TORRENT_HANDLE_HPP

#include <nan.h>
#include <libtorrent/torrent_handle.hpp>
#include <libtorrent/torrent_info.hpp>
#include <libtorrent/peer_info.hpp>

#include "torrent_info.h"
#include "torrent_status.hpp"
#include "endpoint.hpp"
#include "peer_info.hpp"
#include "sha1_hash.hpp"

class TorrentHandle : public Nan::ObjectWrap {
  public:
    static NAN_MODULE_INIT(Init);
    static v8::Local<v8::Object> New(libtorrent::torrent_handle th);
    static libtorrent::torrent_handle* Unwrap(const v8::Local<v8::Object>& obj) {
      TorrentHandle* th = Nan::ObjectWrap::Unwrap<TorrentHandle>(obj);
      return &th->th_;
    };
    libtorrent::torrent_handle th_;

  private:
    static Nan::Persistent<v8::Function> constructor;

    static NAN_METHOD(NewInstance);
    static NAN_METHOD(get_peer_info);
    static NAN_METHOD(status);
    static NAN_METHOD(get_download_queue);
    static NAN_METHOD(file_progress);
    //static NAN_METHOD(trackers);
    //static NAN_METHOD(replace_trackers);
    //static NAN_METHOD(add_tracker);
    static NAN_METHOD(add_url_seed);
    static NAN_METHOD(remove_url_seed);
    static NAN_METHOD(url_seeds);
    static NAN_METHOD(add_http_seed);
    static NAN_METHOD(remove_http_seed);
    static NAN_METHOD(http_seeds);
    static NAN_METHOD(set_metadata);
    static NAN_METHOD(is_valid);
    //static NAN_METHOD(has_metadata);
    static NAN_METHOD(pause);
    static NAN_METHOD(resume);
    static NAN_METHOD(clear_error);
    static NAN_METHOD(set_priority);
    static NAN_METHOD(super_seeding);

    static NAN_METHOD(auto_managed);
    static NAN_METHOD(queue_position);
    static NAN_METHOD(queue_position_up);
    static NAN_METHOD(queue_position_down);
    static NAN_METHOD(queue_position_top);
    static NAN_METHOD(queue_position_bottom);

    /*#ifndef TORRENT_DISABLE_RESOLVE_COUNTRIES
    static NAN_METHOD(resolve_countries);
    #endif*/

    static NAN_METHOD(add_piece);
    static NAN_METHOD(read_piece);
    static NAN_METHOD(have_piece);
    static NAN_METHOD(set_piece_deadline);
    static NAN_METHOD(reset_piece_deadline);
    static NAN_METHOD(piece_availability);
    static NAN_METHOD(piece_priority);
    static NAN_METHOD(prioritize_pieces);
    static NAN_METHOD(piece_priorities);
    static NAN_METHOD(prioritize_files);
    static NAN_METHOD(file_priorities);
    static NAN_METHOD(file_priority);
    #ifndef TORRENT_NO_DEPRECATE
      static NAN_METHOD(use_interface);
    #endif
    static NAN_METHOD(save_resume_data);
    static NAN_METHOD(need_save_resume_data);
    static NAN_METHOD(force_reannounce);

  #ifndef TORRENT_DISABLE_DHT
    static NAN_METHOD(force_dht_announce);
  #endif

    static NAN_METHOD(scrape_tracker);
    static NAN_METHOD(set_upload_mode);
    static NAN_METHOD(set_share_mode);
    static NAN_METHOD(flush_cache);
    static NAN_METHOD(apply_ip_filter);
    static NAN_METHOD(set_upload_limit);
    static NAN_METHOD(upload_limit);
    static NAN_METHOD(set_download_limit);
    static NAN_METHOD(download_limit);
    static NAN_METHOD(set_sequential_download);
    static NAN_METHOD(connect_peer);
    //static NAN_METHOD(save_path);
    //static NAN_METHOD(make_magnet_link);
    static NAN_METHOD(set_max_uploads);
    static NAN_METHOD(max_uploads);
    static NAN_METHOD(set_max_connections);
    static NAN_METHOD(max_connections);
    //static NAN_METHOD(set_tracker_login);
    static NAN_METHOD(move_storage);
    static NAN_METHOD(info_hash);
    static NAN_METHOD(force_recheck);
    static NAN_METHOD(rename_file);
    static NAN_METHOD(set_ssl_certificate);

    static NAN_METHOD(torrent_file);
};

#endif // LIBTORRENT_NODE_TORRENT_HANDLE_HPP
