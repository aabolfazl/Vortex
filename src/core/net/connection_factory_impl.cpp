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


#include "connection_factory_impl.h"
#include "client_connection_impl.h"
#include "core/io/socket_io_handle_impl.h"

namespace vortex::core::network {

auto connection_factory_impl::create_tcp_connection(event::dispatcher& dispatcher,
                                                    ipv4_ptr address) -> client_connection_ptr {

    auto io_handlr_ptr = vortex::core::socket_io_handle_impl::create_tcp();
    if (!io_handlr_ptr) {
        return nullptr;
    }

    io_handlr_ptr->set_blocking(false);
    const int opt = 1;
    io_handlr_ptr->set_socket_option(SOL_SOCKET, SO_REUSEPORT, &opt, sizeof opt);

    return std::make_shared<client_connection_impl>(dispatcher, address, std::move(io_handlr_ptr));
}


} // namespace vortex::core::network
