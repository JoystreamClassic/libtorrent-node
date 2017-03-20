/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, January 12 2017
 */

 #ifndef LIBTORRENT_NODE_ALERT_HPP
 #define LIBTORRENT_NODE_ALERT_HPP

#include <nan.h>
#include <boost/optional.hpp>

namespace libtorrent {
    class alert;
    struct torrent_alert;
    struct peer_alert; // todo
    struct tracker_alert;

    // alert
    struct udp_error_alert; // todo
    struct external_ip_alert; // todo
    struct listen_failed_alert; // todo
    struct listen_succeeded_alert; // todo
    struct portmap_error_alert; // todo
    struct portmap_alert;
    struct portmap_log_alert; // Error !
    struct dht_announce_alert; // todo
    struct dht_get_peers_alert;
    struct dht_bootstrap_alert;
    struct session_stats_alert; // todo
    struct dht_error_alert; // todo
    struct dht_immutable_item_alert; // todo
    struct dht_mutable_item_alert; // todo
    struct dht_put_alert; // todo
    struct i2p_alert; // todo
    struct dht_outgoing_get_peers_alert; // todo
    //struct log_alert; // Error
    struct lsd_error_alert; // todo
    struct dht_stats_alert; // todo
    struct dht_log_alert; // todo
    struct dht_pkt_alert; // todo
    struct dht_direct_response_alert; // todo
    //struct session_error_alert; // todo

    // torrent_alert
    struct dht_get_peers_reply_alert; // todo
    struct metadata_received_alert;
    struct metadata_failed_alert; // todo
    struct add_torrent_alert; // todo
    struct torrent_finished_alert;
    struct state_update_alert; // todo
    struct tracker_alert; // todo
    struct torrent_added_alert;
    struct read_piece_alert; // todo
    struct file_completed_alert; // todo
    struct file_renamed_alert;
    struct file_rename_failed_alert; // todo
    struct performance_alert; // todo
    struct state_changed_alert;
    struct torrent_removed_alert;
    struct torrent_resumed_alert;
    struct save_resume_data_alert; // todo
    struct save_resume_data_failed_alert; // todo
    struct torrent_paused_alert;
    struct torrent_checked_alert;
    struct storage_moved_alert;
    struct storage_moved_failed_alert; // todo
    struct torrent_deleted_alert;
    struct torrent_delete_failed_alert; // todo
    struct piece_finished_alert; // todo
    struct hash_failed_alert; // todo
    struct url_seed_alert; // todo
    struct file_error_alert; // todo
    struct fastresume_rejected_alert; // todo
    struct stats_alert; // todo
    struct cache_flushed_alert;
    struct anonymous_mode_alert;
    struct torrent_need_cert_alert; // todo
    struct incoming_connection_alert;
    //struct torrent_log_alert;
    struct torrent_error_alert; // todo

    // tracker_alert
    struct tracker_error_alert; // todo
    struct tracker_warning_alert; // todo
    struct scrape_reply_alert;
    struct scrape_failed_alert; // todo
    struct tracker_reply_alert;
    struct tracker_warning_alert; // todo
    struct dht_reply_alert;
    struct tracker_announce_alert;
    struct trackerid_alert;

    // peer_alert
    struct block_downloading_alert; // todo
    struct peer_connect_alert;
    struct peer_disconnected_alert; // todo
    struct peer_ban_alert;
    struct peer_unsnubbed_alert;
    struct peer_snubbed_alert;
    struct peer_error_alert; // todo
    struct invalid_request_alert; // todo
    struct request_dropped_alert; // todo
    struct block_timeout_alert; // todo
    struct block_finished_alert; // todo
    struct unwanted_block_alert; // todo
    struct peer_blocked_alert; // Error static cast on peer_alert ?
    struct lsd_peer_alert;
    //struct peer_log_alert; // todo
    struct incoming_request_alert; // todo
    struct picker_log_alert; // todo

namespace node {
namespace alert_types {

/**
 * Routines for converting libtorrent alerts to javascript
 * objects. No constructors are offered, since creating
 * these alerts is not possible when using libtorrent natively.
 * Moreover, javascript objects are not wrapping any c++ class,
 * we rather copy all member data into the javascript objects, since
 * only data members are present in alerts.
 */

NAN_MODULE_INIT(InitAlertTypes);

boost::optional<v8::Local<v8::Object>> alertEncoder(const libtorrent::alert *a);

// Abstract (base) alerts
v8::Local<v8::Object> encode(const libtorrent::alert *);
v8::Local<v8::Object> encode(const libtorrent::torrent_alert *);
v8::Local<v8::Object> encode(const libtorrent::peer_alert *);
v8::Local<v8::Object> encode(const libtorrent::tracker_alert *);

// Non-virtual alerts
v8::Local<v8::Object> encode(const libtorrent::udp_error_alert *);
v8::Local<v8::Object> encode(const libtorrent::external_ip_alert *);
v8::Local<v8::Object> encode(const libtorrent::listen_failed_alert *);
v8::Local<v8::Object> encode(const libtorrent::portmap_error_alert *);
v8::Local<v8::Object> encode(const libtorrent::portmap_alert *);
//v8::Local<v8::Object> encode(const libtorrent::portmap_log_alert *);
v8::Local<v8::Object> encode(const libtorrent::dht_announce_alert *);
v8::Local<v8::Object> encode(const libtorrent::dht_get_peers_alert *);
v8::Local<v8::Object> encode(const libtorrent::dht_bootstrap_alert *);
v8::Local<v8::Object> encode(const libtorrent::incoming_connection_alert *);
v8::Local<v8::Object> encode(const libtorrent::session_stats_alert *);
v8::Local<v8::Object> encode(const libtorrent::dht_error_alert *);
v8::Local<v8::Object> encode(const libtorrent::dht_immutable_item_alert *);
v8::Local<v8::Object> encode(const libtorrent::dht_put_alert *);
v8::Local<v8::Object> encode(const libtorrent::dht_outgoing_get_peers_alert *);
// v8::Local<v8::Object> encode(const libtorrent::log_alert *);
v8::Local<v8::Object> encode(const libtorrent::lsd_error_alert *);
v8::Local<v8::Object> encode(const libtorrent::dht_stats_alert *);
v8::Local<v8::Object> encode(const libtorrent::dht_log_alert *);
v8::Local<v8::Object> encode(const libtorrent::dht_pkt_alert *);
v8::Local<v8::Object> encode(const libtorrent::dht_direct_response_alert *);
//v8::Local<v8::Object> encode(const libtorrent::session_error_alert *);
v8::Local<v8::Object> encode(const libtorrent::dht_get_peers_reply_alert *);
v8::Local<v8::Object> encode(const libtorrent::listen_succeeded_alert *);
v8::Local<v8::Object> encode(const libtorrent::state_update_alert *);

// Non-virtual (torrent) alerts
v8::Local<v8::Object> encode(const libtorrent::torrent_added_alert *);
v8::Local<v8::Object> encode(const libtorrent::metadata_received_alert *);
v8::Local<v8::Object> encode(const libtorrent::metadata_failed_alert *);
v8::Local<v8::Object> encode(const libtorrent::add_torrent_alert *);
v8::Local<v8::Object> encode(const libtorrent::torrent_finished_alert *);
v8::Local<v8::Object> encode(const libtorrent::torrent_removed_alert *);
v8::Local<v8::Object> encode(const libtorrent::torrent_resumed_alert *);
v8::Local<v8::Object> encode(const libtorrent::save_resume_data_alert *);
v8::Local<v8::Object> encode(const libtorrent::save_resume_data_failed_alert *);
v8::Local<v8::Object> encode(const libtorrent::torrent_paused_alert *);
v8::Local<v8::Object> encode(const libtorrent::torrent_checked_alert *);
v8::Local<v8::Object> encode(const libtorrent::read_piece_alert *);
v8::Local<v8::Object> encode(const libtorrent::piece_finished_alert *);
v8::Local<v8::Object> encode(const libtorrent::file_completed_alert *);
v8::Local<v8::Object> encode(const libtorrent::file_renamed_alert *);
v8::Local<v8::Object> encode(const libtorrent::performance_alert *);
v8::Local<v8::Object> encode(const libtorrent::state_changed_alert *);
v8::Local<v8::Object> encode(const libtorrent::hash_failed_alert *);
v8::Local<v8::Object> encode(const libtorrent::storage_moved_failed_alert *);
v8::Local<v8::Object> encode(const libtorrent::torrent_delete_failed_alert *);
v8::Local<v8::Object> encode(const libtorrent::url_seed_alert *);
v8::Local<v8::Object> encode(const libtorrent::file_error_alert *);
v8::Local<v8::Object> encode(const libtorrent::fastresume_rejected_alert *);
v8::Local<v8::Object> encode(const libtorrent::stats_alert *);
v8::Local<v8::Object> encode(const libtorrent::cache_flushed_alert *);
v8::Local<v8::Object> encode(const libtorrent::anonymous_mode_alert *);
v8::Local<v8::Object> encode(const libtorrent::torrent_need_cert_alert *);
//v8::Local<v8::Object> encode(const libtorrent::torrent_log_alert *);
v8::Local<v8::Object> encode(const libtorrent::peer_alert *);
v8::Local<v8::Object> encode(const libtorrent::tracker_alert *);


// Non-virtual (peer) alerts
v8::Local<v8::Object> encode(const libtorrent::peer_ban_alert *);
v8::Local<v8::Object> encode(const libtorrent::peer_unsnubbed_alert *);
v8::Local<v8::Object> encode(const libtorrent::peer_snubbed_alert *);
v8::Local<v8::Object> encode(const libtorrent::peer_error_alert *);
v8::Local<v8::Object> encode(const libtorrent::peer_connect_alert *);
v8::Local<v8::Object> encode(const libtorrent::peer_disconnected_alert *);
v8::Local<v8::Object> encode(const libtorrent::invalid_request_alert *);
v8::Local<v8::Object> encode(const libtorrent::request_dropped_alert *);
v8::Local<v8::Object> encode(const libtorrent::block_finished_alert *);
v8::Local<v8::Object> encode(const libtorrent::block_timeout_alert *);
v8::Local<v8::Object> encode(const libtorrent::block_downloading_alert *);
v8::Local<v8::Object> encode(const libtorrent::unwanted_block_alert *);
//v8::Local<v8::Object> encode(const libtorrent::peer_blocked_alert *);
v8::Local<v8::Object> encode(const libtorrent::lsd_peer_alert *);
//v8::Local<v8::Object> encode(const libtorrent::peer_log_alert *);
v8::Local<v8::Object> encode(const libtorrent::incoming_request_alert *);
v8::Local<v8::Object> encode(const libtorrent::picker_log_alert *);

// Non-virtual (tracker) alerts
v8::Local<v8::Object> encode(const libtorrent::tracker_error_alert *);
v8::Local<v8::Object> encode(const libtorrent::tracker_warning_alert *);
v8::Local<v8::Object> encode(const libtorrent::scrape_reply_alert *);
v8::Local<v8::Object> encode(const libtorrent::scrape_failed_alert *);
v8::Local<v8::Object> encode(const libtorrent::tracker_reply_alert *);
v8::Local<v8::Object> encode(const libtorrent::dht_reply_alert *);
v8::Local<v8::Object> encode(const libtorrent::tracker_announce_alert *);
v8::Local<v8::Object> encode(const libtorrent::trackerid_alert *);

}
}
}

#endif // LIBTORRENT_NODE_ALERT_HPP
