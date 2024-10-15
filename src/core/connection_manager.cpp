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

namespace vortex::core {
connection_manager::connection_manager(const config::config_ptr config_ptr) :
    _config_ptr(config_ptr),
    _worker_ptr(std::shared_ptr<event::io_uring_worker>()),
    _connection_acceptor_ptr(std::make_unique<connection_acceptor>(_worker_ptr, config_ptr->listener.port)) {

    _connection_acceptor_ptr->setAcceptCallback([&](int fd) { on_new_connection_established(fd); });
}

void connection_manager::on_new_connection_established(int fd) {
}

void connection_manager::start_accept_connections() {
    _connection_acceptor_ptr->listen();
}

connection_manager::~connection_manager() {
}

} // namespace vortex::core
