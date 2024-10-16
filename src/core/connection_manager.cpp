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

#include <memory>
#include "config/Config.h"
#include "connection_acceptor.h"
#include "connection_manager.h"
#include "io_uring_worker.h"
#include "logger/logger.h"

namespace vortex::core {
connection_manager::connection_manager() :
    _worker_ptr(std::make_shared<event::io_uring_worker>()),
    _connection_acceptor_ptr(std::make_unique<connection_acceptor>(_worker_ptr, config::config()->listener.port)) {

    logger::info("connection_manager");

    _connection_acceptor_ptr->setAcceptCallback([&](int fd) { on_new_connection_established(fd); });
}

void connection_manager::on_new_connection_established(int fd) {
    logger::info("on_new_connection_established {}", fd);

    // select a server acording to the selection alghoritim
    //auto client = std::make_shared<client_connection>();


}

void connection_manager::start_accept_connections() {
    _worker_ptr->loop();
}

connection_manager::~connection_manager() {
}

} // namespace vortex::core
