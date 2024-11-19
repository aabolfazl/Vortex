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

#ifndef VORTEX_TCPSERVER_H
#define VORTEX_TCPSERVER_H


#include "config/config.h"
#include "connection_manager.h"

namespace vortex::core {
class tcp_server final {
public:
    explicit tcp_server();

    auto start() -> void;

    auto stop() -> void;

private:
    auto on_new_connection(int fd) -> void;

    connection_manager_ptr _connection_manager_ptr;
};
} // namespace vortex::core


#endif // VORTEX_TCPSERVER_H
