/*
  * Copyright © 2024 Vortex project
  *
  * This is the source code of the Vortex project.
  * It is licensed under the MIT License; you should have received a copy
  * of the license in this archive (see LICENSE).
  *
  * Author: Abolfazl Abbasi
  *
  */

#ifndef VORTEX_TCPSERVER_H
#define VORTEX_TCPSERVER_H


#include "../Vortex.h"
#include "config/Config.h"
#include "connection_acceptor.h"
#include "config/ConfigLoader.h"
#include "connection_manager.h"

namespace vortex::core {
class tcp_server : public SharedClass<tcp_server> {
public:
    explicit tcp_server(config::config_ptr config_ptr);

    auto start() -> void;

    auto stop() -> void;

private:
    auto on_new_connection(int fd) -> void;

    std::shared_ptr<config::Config> config;
    connection_manager_ptr _connection_manager_ptr;

};
}


#endif //VORTEX_TCPSERVER_H
