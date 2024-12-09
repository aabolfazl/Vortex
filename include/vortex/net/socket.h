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
#include "common/address.h"
#include "common/platform.h"
#include "common/traits.h"
#include "vortex/network/io_handle.h"
#include "functional"

namespace vortex::core::network {
using accept_callback = std::function<void(int fd)>;

/*
 * This class is an interface for all socket classes.
 * we have three implementations for this interface:
 * 1. connection_socket uses for client and backend connections
 * 2. listener_socket uses for listening to incoming connections and accept them
 */

class socket : public traits::non_copyable<socket> {
public:
    virtual ~socket() = default;

    virtual auto iohandle() const noexcept -> io_handle& = 0;

    virtual auto start_accept() noexcept -> void = 0;
    virtual auto connect(ipv4 address) noexcept -> void = 0;
    virtual auto start_read() noexcept -> void = 0;
    virtual auto start_write(const uint8_t *data, size_t length) noexcept -> void = 0;
    virtual auto close() noexcept -> void = 0;
    virtual auto fd() const noexcept -> os_fd_t = 0;

    virtual auto ipv4() const noexcept -> const ipv4& = 0;
};

using socket_ptr = std::unique_ptr<socket>;

} // namespace vortex::core
