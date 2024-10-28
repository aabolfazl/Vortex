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

#include "async_socket.h"
#include "socket_handle.h"
#include "common/traits.h"

namespace vortex::core {
class async_socket_factory : public traits::non_copyable<async_socket_factory>,
                             public traits::non_moveable<async_socket_factory> {
public:
    virtual ~async_socket_factory() = default;

    virtual auto create_acceptor(event::os_fd_t fd) noexcept -> async_socket_ptr = 0;
    virtual auto create_connection(event::os_fd_t fd) noexcept -> async_socket_ptr = 0;
};

using async_socket_factory_ptr = std::shared_ptr<async_socket_factory>;

}
