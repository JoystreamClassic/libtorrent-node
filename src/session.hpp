#ifndef LIBTORRENT_NODE_SESSION_HPP
#define LIBTORRENT_NODE_SESSION_HPP

#include <nan.h>
#include "alert.hpp"
#include "torrent_handle.h"
#include "add_torrent_params.hpp"
#include "plugin.hpp"
#include "sha1_hash.hpp"
#include <iostream>
#include <libtorrent/session.hpp>
#include <libtorrent/fingerprint.hpp>
#include <vector>

namespace libtorrent {
namespace node {

class Session : public Nan::ObjectWrap {
  public:
    static NAN_MODULE_INIT(Init);

  private:
    Session(boost::shared_ptr<libtorrent::session> session);
    static libtorrent::settings_pack session_settings(bool enableDHT) noexcept;


    boost::shared_ptr<libtorrent::session> _session;
    static Nan::Persistent<v8::Function> constructor;
    // Persistent handle set in set_alert_notify, signaling alert queue becoming non-empty
    static Nan::Callback _alertNotifier;

    // Alert encoders used, in order.
    std::vector<AlertEncoder> _encoders;

    static NAN_METHOD(New);
    static NAN_METHOD(add_torrent);
    static NAN_METHOD(remove_torrent);
    static NAN_METHOD(listen_port);
    static NAN_METHOD(post_torrent_updates);
    static NAN_METHOD(pause);
    static NAN_METHOD(is_paused);
    static NAN_METHOD(resume);
    static NAN_METHOD(find_torrent);

#ifndef TORRENT_DISABLE_EXTENSIONS
    static NAN_METHOD(add_extension);
#endif // TORRENT_DISABLE_EXTENSIONS

    static NAN_METHOD(pop_alerts);
    static NAN_METHOD(set_alert_notify);
    static NAN_METHOD(dht_announce);
    static NAN_METHOD(dht_get_peers);

};

}
}

#endif // LIBTORRENT_NODE_SESSION_HPP
