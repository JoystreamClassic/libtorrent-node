/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Lola Rigaut-Luczack <rllola80@gmail.com>, January 24 2017
 */

#ifndef LIBTORRENT_NODE_ERROR_CODE_HPP
#define LIBTORRENT_NODE_ERROR_CODE_HPP

#include <nan.h>
#include <libtorrent/error_code.hpp>

namespace libtorrent {
namespace node {
namespace error_code {

  v8::Local<v8::Object> encode(const libtorrent::error_code & a);
  libtorrent::error_code decode(const v8::Local<v8::Object> & o);

}}}

#endif // LIBTORRENT_NODE_ERROR_CODE_HPP
