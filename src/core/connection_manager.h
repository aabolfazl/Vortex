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

#ifndef CONNECTIONMANAGER_H
#define CONNECTIONMANAGER_H

#include <memory>
#include <mutex>
#include <sys/types.h>
#include <unordered_map>
#include <vector>
#include "client/client_connection.h"
#include "config/Config.h"
#include "connection_acceptor.h"
#include "io_uring_worker.h"

namespace vortex::core {
class connection_manager final {
public:
    explicit connection_manager();
    ~connection_manager();

    void start_accept_connections();

private:
    void on_new_connection_established(int fd);
    event::io_uring_worker_ptr _worker_ptr;
    connection_acceptor_ptr _connection_acceptor_ptr;

    std::unordered_map<int, client_connection_ptr> client_connections;
};

using connection_manager_ptr = std::shared_ptr<connection_manager>;

} // namespace vortex::core

#endif // PROCESSMANAGER_H
