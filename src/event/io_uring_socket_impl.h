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

#include "core/interfaces/async_socket.h"
#include "core/interfaces/socket_handle.h"
#include "core/interfaces/event/io_uring_socket.h"
#include "core/interfaces/event/io_uring_worker.h"

namespace vortex::event {

class io_uring_socket_impl final : public io_uring_socket {
public:
    explicit io_uring_socket_impl(os_fd_t fd,const io_uring_worker_ptr& worker, io_uring_socket_type type);
    ~io_uring_socket_impl() override;

    auto on_accept(io_request *req, int32_t result) const noexcept -> void override;
    auto on_connect(io_request *req, int32_t result) noexcept -> void override;
    auto on_read(io_request *req, int32_t result) noexcept -> void override;
    auto on_write(io_request *req, int32_t result) noexcept -> void override;
    auto on_close(io_request *req, int32_t result) noexcept -> void override;
    auto on_cancel(io_request *req, int32_t result) noexcept -> void override;
    auto on_shutdown(io_request *req, int32_t result) noexcept -> void override;

    auto get_status() const noexcept -> io_uring_socket_status override;

    auto start_accept() noexcept -> void override;
    auto connect(core::ipv4 address) noexcept -> void override;
    auto start_read() noexcept -> void override;
    auto start_write(const uint8_t *data, size_t length) noexcept -> void override;
    auto close() noexcept -> void override;
    auto shutdown(int how) noexcept -> void override;
    auto get_fd() const noexcept -> os_fd_t override;

    auto set_event_handler(core::socket_event_handler_ptr handler) noexcept -> void override;

    auto has_event_handler() const noexcept -> bool override;

private:
    core::socket_handle socket_handle_{-1};
    io_uring_socket_type type_{io_uring_socket_type::unknown};
    io_uring_socket_status status_{};

    io_uring_worker_ptr worker_;
    core::socket_event_handler_ptr event_handler_;

    bool _has_event_handler{false};
};
}
