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

#include "socket_event_handler.h"
#include "common/address.h"
#include "common/traits.h"
#include "event/io_uring.h"

namespace vortex::core {
using accept_callback = std::function<void(int fd)>;

class async_socket : public traits::non_copyable<socket_event_handler>,
                     public traits::non_moveable<socket_event_handler> {
public:
    virtual ~async_socket() = default;

    virtual auto start_accept() noexcept -> void = 0;
    virtual auto connect(ipv4 address) noexcept -> void = 0;
    virtual auto start_read() noexcept -> void = 0;
    virtual auto start_write(const uint8_t *data, size_t length) noexcept -> void = 0;
    virtual auto close() noexcept -> void = 0;
    virtual auto set_event_handler(std::shared_ptr<socket_event_handler> handler) noexcept -> void = 0;
    virtual auto shutdown(int how) noexcept -> void = 0;
    virtual auto get_fd() const noexcept -> event::os_fd_t = 0;

    virtual auto has_event_handler() const noexcept -> bool = 0;

};

using async_socket_ptr = std::unique_ptr<async_socket>;

}
