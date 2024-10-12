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
#include "connection_acceptor.h"
#include "config/ConfigLoader.h"

namespace vortex::core {
class tcp_server : public SharedClass<tcp_server> {
public:
    explicit tcp_server(
        const std::shared_ptr<config::ConfigLoader>& configLoader,
        const event::io_uring_worker_ptr& ioUringWorker
);

    auto start() -> void;

    auto stop() -> void;

private:
    auto on_new_connection(int fd) -> void;

    std::unique_ptr<connection_acceptor> acceptor;
    event::io_uring_worker_ptr ioUringWorker;
    std::shared_ptr<config::Config> config;
};
}


#endif //VORTEX_TCPSERVER_H