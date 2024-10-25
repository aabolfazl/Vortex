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

#include "core/interfaces/event/io_uring_worker.h"

namespace vortex::core {
class server_connection final {
public:
    explicit server_connection(event::os_fd_t socket_fd);
    ~server_connection();

private:
    event::io_uring_worker_ptr _worker_ptr;
};

using server_connection_ptr = std::shared_ptr<server_connection>;

} // namespace vortex::core
