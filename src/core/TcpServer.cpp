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

#include "TcpServer.h"
#include <chrono>
#include <thread>

namespace vortex::core {

TcpServer::TcpServer(
    const std::shared_ptr<config::ConfigLoader> &configLoader,
    const std::shared_ptr<event::EventLoop> &eventLoop
) : config(configLoader->load()), eventLoop(eventLoop) {
    const auto port = config->listener.port;

    acceptor = std::make_unique<ConnectionAcceptor>(eventLoop, port);
    acceptor->setAcceptCallback(std::bind(&TcpServer::onNewConnection, this, std::placeholders::_1));
}

auto TcpServer::onNewConnection(int fd) -> void {
    std::cerr << "onNewClientConnected " << fd << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    close(fd);
    std::cerr << "onNewClientClosed " << fd << std::endl;
}

auto TcpServer::start() -> void {
    eventLoop->loop();
}

auto TcpServer::stop() -> void {

}

}