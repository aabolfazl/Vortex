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

#pragma once

#include <memory>

#include "core/config/Config.h"
#include "core/interfaces/event/io_uring.h"
#include "core/interfaces/event/io_uring_worker.h"
#include "core/server/server_connection.h"

namespace vortex::core {
class client_connection final {
public:
    explicit client_connection(event::os_fd_t socket_fd, server_connection_ptr &server_connection);
    ~client_connection();

private:
    config::config_ptr _config_ptr;
    event::io_uring_worker_ptr _worker_ptr;

    server_connection_ptr _server_connection;
};

using client_connection_ptr = std::shared_ptr<client_connection>;

} // namespace vortex::core
