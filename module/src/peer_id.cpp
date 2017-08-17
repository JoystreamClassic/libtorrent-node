/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, January 16 2017
 */

#include "peer_id.hpp"
#include "sha1_hash.hpp" // encoder and decoder for sha1_hash
#include "address.hpp"
#include "utils.hpp"

namespace libtorrent {
namespace node {
namespace peer_id {

// Note: libtorrent::peer_id is just a typedef of libtorrent::sha1_hash so we
// will reuse the ecoder and decoder for sha1_hash
v8::Local<v8::String> encode(const libtorrent::peer_id & pid) {
    return node::sha1_hash::encode(pid);
}

libtorrent::peer_id decode(const v8::Local<v8::Value> & v) {
  return node::sha1_hash::decode(v);

}

}
}
}
