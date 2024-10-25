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

#include "functional"
#include "memory"
#include "common/traits.h"

namespace vortex::event {
using accept_callback = std::function<void(int fd)>;

class io_uring_socket : traits::non_copyable<io_uring_socket>, traits::non_moveable<io_uring_socket> {
public:
    virtual ~io_uring_socket() = default;

    virtual auto get_fd() const noexcept -> os_fd_t = 0;
    virtual auto close() noexcept -> void = 0;
    virtual auto enable_read() noexcept -> void = 0;
    virtual auto disabler_read() noexcept -> void = 0;
    virtual auto enable_close_event(bool enable) noexcept -> void = 0;
    virtual auto connect(uint32_t address) noexcept -> void = 0;
    virtual auto write(uint8_t &data) noexcept -> void = 0;
    virtual auto write(const uint8_t *slices, uint64_t num_slice) noexcept -> uint64_t = 0;
    virtual auto shutdown(int how) noexcept -> void = 0;
    virtual auto on_accept(io_request *req, int32_t result) const noexcept -> void = 0;
    virtual auto on_connect(io_request *req, int32_t result) noexcept -> void = 0;
    virtual auto on_read(io_request *req, int32_t result) noexcept -> void = 0;
    virtual auto on_write(io_request *req, int32_t result) noexcept -> void = 0;
    virtual auto on_close(io_request *req, int32_t result) noexcept -> void = 0;
    virtual auto on_cancel(io_request *req, int32_t result) noexcept -> void = 0;
    virtual auto on_shutdown(io_request *req, int32_t result) noexcept -> void = 0;
    virtual auto set_accept_call_back(const accept_callback &callback) noexcept -> void = 0;
    virtual auto get_status() const noexcept -> io_uring_socket_status = 0;
};
} // namespace vortex::event
