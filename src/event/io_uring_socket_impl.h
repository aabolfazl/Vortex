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

#include "core/interfaces/socket_handle.h"
#include "core/interfaces/event/io_uring_socket.h"

namespace vortex::event {

class io_uring_socket_impl final : public io_uring_socket {
public:
    explicit io_uring_socket_impl(os_fd_t fd, io_uring_socket_type type);
    ~io_uring_socket_impl() override = default;

    auto get_fd() const noexcept -> os_fd_t override;
    auto close() noexcept -> void override;
    auto enable_read() noexcept -> void override;
    auto disabler_read() noexcept -> void override;
    auto enable_close_event(bool enable) noexcept -> void override;
    auto connect(uint32_t address) noexcept -> void override;
    auto write(uint8_t &data) noexcept -> void override;
    auto write(const uint8_t *slices, uint64_t num_slice) noexcept -> uint64_t override;
    auto shutdown(int how) noexcept -> void override;
    auto on_accept(io_request *req, int32_t result) const noexcept -> void override;
    auto on_connect(io_request *req, int32_t result) noexcept -> void override;
    auto on_read(io_request *req, int32_t result) noexcept -> void override;
    auto on_write(io_request *req, int32_t result) noexcept -> void override;
    auto on_close(io_request *req, int32_t result) noexcept -> void override;
    auto on_cancel(io_request *req, int32_t result) noexcept -> void override;
    auto on_shutdown(io_request *req, int32_t result) noexcept -> void override;
    auto set_accept_call_back(const accept_callback &callback) noexcept -> void override;
    auto get_status() const noexcept -> io_uring_socket_status override;

private:
    core::socket_handle socket_handle_{-1};
    io_uring_socket_type type_{io_uring_socket_type::unknown};
    accept_callback accept_callback_ = nullptr;
    io_uring_socket_status status_{};
};
}
