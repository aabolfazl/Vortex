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

#include <chrono>
#include <memory>
#include <thread>
#include "tcp_server.h"

#include "config/config.h"
#include "connection_manager.h"
#include "logger/logger.h"

namespace vortex::core {
tcp_server::tcp_server() : _connection_manager_ptr(std::make_shared<connection_manager>()) {
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
    logger::info("tcp server started");
    _connection_manager_ptr->start_accept_connections();
}

auto tcp_server::stop() -> void {
}
} // namespace vortex::core
