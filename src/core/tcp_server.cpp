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

#include "tcp_server.h"
#include <chrono>
#include <thread>

#include "logger/logger.h"

namespace vortex::core {
tcp_server::tcp_server(
    const std::shared_ptr<config::ConfigLoader>& configLoader,
    const event::io_uring_worker_ptr& ioUringWorker
) : ioUringWorker(ioUringWorker), config(configLoader->load()) {
    const auto port = config->listener.port;

    acceptor = std::make_unique<connection_acceptor>(ioUringWorker, port);
    acceptor->setAcceptCallback([this](const int fd) {
        on_new_connection(fd);
    });
}

auto tcp_server::on_new_connection(int fd) -> void {
    logger::info("onNewClientConnected {}", fd);
    std::this_thread::sleep_for(std::chrono::milliseconds(10));
    const std::string msg = "Hi man fd: " + std::to_string(fd) + "\n";

    write(fd, msg.data(), msg.size());
    close(fd);
    logger::info("onNewClientClosed {}", fd);
}

auto tcp_server::start() -> void {
    ioUringWorker->loop();
}

auto tcp_server::stop() -> void {}
}
