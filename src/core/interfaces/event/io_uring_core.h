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
#include "common/address.h"
#include "core/interfaces/event/async_event.h"

namespace vortex::event {

class io_uring_core {
public:
    virtual ~io_uring_core() = default;

    virtual auto prepare_accept(event::accept_operation_ptr ptr) noexcept -> io_uring_result = 0;
    virtual auto prepare_connect(os_fd_t fd, const core::ipv4 &address,
                                 io_request *user_data) noexcept -> io_uring_result = 0;
    virtual auto prepare_readv(os_fd_t fd, const iovec *iovecs, unsigned nr_vecs, off_t offset,
                               io_request *user_data) noexcept -> io_uring_result = 0;
    virtual auto prepare_writev(os_fd_t fd, const iovec *iovecs, unsigned nr_vecs, off_t offset,
                                io_request *user_data) noexcept -> io_uring_result = 0;
    virtual auto prepare_close(os_fd_t fd, io_request *user_data) noexcept -> io_uring_result = 0;
    virtual auto prepare_cancel(io_request *cancelling_user_data,
                                io_request *user_data) noexcept -> io_uring_result = 0;
    virtual auto prepare_shutdown(os_fd_t fd, int how, io_request *user_data) noexcept -> io_uring_result = 0;
    virtual auto submit() noexcept -> io_uring_result = 0;
    virtual auto run() noexcept -> void = 0;
    virtual auto exit() noexcept -> void = 0;
};

using io_uring_core_ptr = std::unique_ptr<io_uring_core>;
} // namespace vortex::event
