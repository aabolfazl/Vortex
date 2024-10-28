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

#include "event/io_uring_socket_factory.h"
#include "event/io_uring_socket_impl.h"
#include "event/io_uring_worker_impl.h"
#include "logger/logger.h"

namespace vortex::core {
connection_manager::connection_manager() :
    _worker_ptr(std::make_shared<event::io_uring_worker_impl>()),
    _socket_factory_ptr(std::make_shared<event::io_uring_socket_factory>(_worker_ptr)),
    _connection_acceptor_ptr(std::make_shared<connection_acceptor>(_socket_factory_ptr, config::config()->listener.port)) {

    logger::info("connection_manager");

    init_servers_list();
}

auto connection_manager::init_servers_list() -> void {
    auto backends = config::config()->backends;

    for (auto it = backends.begin(); it != backends.end(); ++it) {
        // auto server = std::make_shared<server_connection>(it);
        // _worker_ptr->submit_connect_request();
        // _upstream_server_connections.push_back(server);
        // logger::info("init_servers_list {}", it->ip);
    }

    logger::info("init_servers_list size: {}", backends.size());
}


void connection_manager::on_new_connection_established(int fd) {
    logger::info("on_new_connection_established {}", fd);

    // select a server acording to the selection alghoritim
    //auto client = std::make_shared<client_connection>();


}

void connection_manager::start_accept_connections() {
    _connection_acceptor_ptr->set_accept_callback([&](const int fd) { on_new_connection_established(fd); });
    _connection_acceptor_ptr->start();
    _worker_ptr->loop();
}

connection_manager::~connection_manager() {}

} // namespace vortex::core
