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

#include "vortex/event/dispatcher.h"
#include "vortex/net/connection.h"

namespace vortex::core::network {
class connection_factory_impl {
public:
    connection_factory_impl() = default;
    ~connection_factory_impl() = default;

    auto create_tcp_connection(event::dispatcher& dispatcher_, ipv4_ptr remote_address) -> client_connection_ptr;
};

} // namespace vortex::core::network
