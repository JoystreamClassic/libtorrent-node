/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Lola Rigaut-Luczak <rllola80@gmail.com>, January 18 2017
 */

#ifndef LIBTORRENT_NODE_PEER_INFO_HPP
#define LIBTORRENT_NODE_PEER_INFO_HPP

#include <nan.h>
#include <libtorrent/peer_info.hpp>

#include "endpoint.hpp"
#include "utils.hpp"

namespace libtorrent {
namespace node {
namespace peer_info {

/**
 * PeerInfo is encoded as
 * {
 *  ip : { Endpoint object },
 * }
 */
v8::Local<v8::Object> encode(const libtorrent::peer_info & pi);

}}}

#endif // LIBTORRENT_NODE_PEER_INFO_HPP
