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

#include "vortex/net/socket.h"
#include "common/address.h"

namespace vortex::core::network {


class socket_impl : public socket {
public:
    explicit socket_impl(io_handle_ptr&& io_handle) noexcept;
    ~socket_impl() override;

    auto iohandle() const noexcept -> io_handle& override;
};

} // namespace vortex::core::network
