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
#include "EventLoop.h"
#include "ConnectionAcceptor.h"
#include "config/ConfigLoader.h"

namespace vortex::core {

class TcpServer : public SharedClass<TcpServer> {

public:
    explicit TcpServer(
        const std::shared_ptr<config::ConfigLoader> &configLoader,
        const std::shared_ptr<event::EventLoop> &eventLoop
    );

    auto start() -> void;

    auto stop() -> void;

private:
    auto onNewConnection(int fd) -> void;

    std::unique_ptr<core::ConnectionAcceptor> acceptor;
    std::shared_ptr<event::EventLoop> eventLoop;
    std::shared_ptr<config::Config> config;
};
}


#endif //VORTEX_TCPSERVER_H
