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

#include "io_uring.h"

#include <cstdint>

#include "memory"
#include "common/traits.h"
#include "core/interfaces/async_socket.h"

namespace vortex::event {

class io_uring_socket : public core::async_socket,
                        traits::non_copyable<io_uring_socket>,
                        traits::non_moveable<io_uring_socket> {
public:
    ~io_uring_socket() override = default;

    virtual auto on_accept(io_request *req, int32_t result) const noexcept -> void = 0;
    virtual auto on_connect(io_request *req, int32_t result) noexcept -> void = 0;
    virtual auto on_read(io_request *req, int32_t result) noexcept -> void = 0;
    virtual auto on_write(io_request *req, int32_t result) noexcept -> void = 0;
    virtual auto on_close(io_request *req, int32_t result) noexcept -> void = 0;
    virtual auto on_cancel(io_request *req, int32_t result) noexcept -> void = 0;
    virtual auto on_shutdown(io_request *req, int32_t result) noexcept -> void = 0;

    virtual auto get_status() const noexcept -> io_uring_socket_status = 0;
};

using io_uring_socket_ptr = std::unique_ptr<io_uring_socket>;
} // namespace vortex::event
