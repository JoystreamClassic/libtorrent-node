/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Lola Rigaut-Luczak <rllola80@gmail.com>, January 19 2017
 */

 #ifndef LIBTORRENT_NODE_STATE_T_HPP
 #define LIBTORRENT_NODE_STATE_T_HPP

#include <nan.h>
#include <libtorrent/torrent_status.hpp>

namespace libtorrent {
namespace node {
namespace state_t {

  // Exports object called `state_t` object, which maps
  // libtorrent::torrent_status::state_t enums, as strings, to integers.
  NAN_MODULE_INIT(Init);

  /**
   * Encoding as Number
   */

  v8::Local<v8::Value> createValue(libtorrent::torrent_status::state_t state);
  libtorrent::torrent_status::state_t fromValue(const v8::Local<v8::Value> & v);

}
}
}

#endif // LIBTORRENT_NODE_STATE_T_HPP
