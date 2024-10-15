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

#include "config/Config.h"
#include "connection_acceptor.h"
#include "io_uring_worker.h"
#include <memory>
#include <mutex>
#include <sys/types.h>
#include <vector>

namespace vortex::core {
class connection_manager final {
public:
    explicit connection_manager(config::config_ptr config_ptr);
    ~connection_manager();

    void start_accept_connections();

private:
    void on_new_connection_established(int fd);
    config::config_ptr _config_ptr;
    event::io_uring_worker_ptr _worker_ptr;
    connection_acceptor_ptr _connection_acceptor_ptr;
};

using connection_manager_ptr = std::shared_ptr<connection_manager>;

} // namespace vortex::core

#endif // PROCESSMANAGER_H
