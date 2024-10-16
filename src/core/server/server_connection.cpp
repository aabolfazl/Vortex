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

#include "server/server_connection.h"
#include "io_uring_core.h"
namespace vortex::core {
server_connection::server_connection(const event::os_fd_t fd) {

}

server_connection::~server_connection(){}

} // namespace vortex::core
