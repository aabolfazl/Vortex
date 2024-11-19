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
#include "config/config.h"
#include "connection_manager.h"
#include "logger/logger.h"

namespace vortex::core {
connection_manager::connection_manager() {

    logger::info("connection_manager");

    init_servers_list();
}

auto connection_manager::init_servers_list() -> void {
    auto backends = config::get_config()->backends;

    for (auto it = backends.begin(); it != backends.end(); ++it) {
        //  auto server = std::make_shared<connection>();
        //  _worker_ptr->submit_connect_request();
        //  _upstream_server_connections.push_back(server);
        //  logger::info("init_servers_list {}", it->ip);
    }

    logger::info("init_servers_list size: {}", backends.size());
}


void connection_manager::on_new_connection_established(int fd) {
    logger::info("on_new_connection_established {}", fd);

    // select a server acording to the selection alghoritim
    //auto client = std::make_shared<client_connection>();


}

void connection_manager::start_accept_connections() {

}

connection_manager::~connection_manager() {}

} // namespace vortex::core
