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
    const std::shared_ptr<config::ConfigLoader>& configLoader,
    const event::IoUringWorkerPtr& ioUringWorker
) : ioUringWorker(ioUringWorker), config(configLoader->load()) {
    const auto port = config->listener.port;

    acceptor = std::make_unique<ConnectionAcceptor>(ioUringWorker, port);
    acceptor->setAcceptCallback([this](const int fd) {
        onNewConnection(fd);
    });
}

auto TcpServer::onNewConnection(int fd) -> void {
    std::cout << "onNewClientConnected " << fd << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    const std::string msg = "Hi man fd: " + std::to_string(fd) + "\n";

    write(fd, msg.data(), msg.size());
    close(fd);
    std::cout << "onNewClientClosed " << fd << std::endl;
}

auto TcpServer::start() -> void {
    ioUringWorker->loop();
}

auto TcpServer::stop() -> void {}
}
