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

#include "client_connection.h"

namespace vortex::core {

client_connection::client_connection(event::os_fd_t socket_fd, server_connection_ptr &server_connection_ptr) :
    _server_connection(server_connection_ptr) {
}


client_connection::~client_connection() {
}
} // namespace vortex::core
