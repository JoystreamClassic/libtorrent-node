/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, January 23 2017
 */

 #ifndef LIBTORRENT_NODE_COMMON_HPP
 #define LIBTORRENT_NODE_COMMON_HPP

 #include <nan.h>

 #include <boost/optional.hpp>

 namespace libtorrent {
   class alert;
 namespace node {

   /**
    * @brief Alert converter for this plugin.
    * @param a alert for conversion.
    * @return optional encoded alert
    */
   typedef boost::optional<v8::Local<v8::Object>>(*AlertEncoder)(const libtorrent::alert *);

 }
 }

 #endif // LIBTORRENT_NODE_COMMON_HPP
