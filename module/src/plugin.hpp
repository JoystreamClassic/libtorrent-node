/**
 * Copyright (C) JoyStream - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * Written by Bedeho Mender <bedeho.mender@gmail.com>, January 21 2017
 */

 #ifndef LIBTORRENT_NODE_PLUGIN_HPP
 #define LIBTORRENT_NODE_PLUGIN_HPP

#include <nan.h>

#include "common.hpp"

#include <boost/shared_ptr.hpp>

namespace libtorrent {
  class alert;
  struct plugin;
namespace node {

/**
 * @brief Wraps libtorrent::plugin, intended to be
 * base class for bindings for libtorrent bindings.
 */
class plugin : public Nan::ObjectWrap {

public:

  /**
   * @brief Get alert converter for this plugin.
   */
  virtual AlertEncoder getEncoder() const noexcept = 0;

  /**
   * @brief Returns reference to this plugin.
   */
  virtual boost::shared_ptr<libtorrent::plugin> getPlugin() const noexcept = 0;

};

}
}

#endif // LIBTORRENT_NODE_PLUGIN_HPP
