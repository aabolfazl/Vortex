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

#ifndef SERVER_CONNECTION_H
#define SERVER_CONNECTION_H

#include <memory>
#include <mutex>
#include <sys/types.h>
#include "config/Config.h"
#include "connection_acceptor.h"
#include "io_uring_core.h"
#include "io_uring_worker.h"

namespace vortex::core {
class server_connection final {
public:
    explicit server_connection(event::os_fd_t socket_fd);
    ~server_connection();

private:
    config::config_ptr _config_ptr;
    event::io_uring_worker_ptr _worker_ptr;
};

using server_connection_ptr = std::shared_ptr<server_connection>;

} // namespace vortex::core

#endif // SERVER_CONNECTION_H
