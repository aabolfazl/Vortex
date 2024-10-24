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

namespace vortex::event {

class io_uring_core {
public:
    virtual ~io_uring_core() = default;

    auto prepare_accept(io_uring_socket &socket) noexcept -> io_uring_result;

    auto prepare_readv(os_fd_t fd, const iovec *iovecs, unsigned nr_vecs, off_t offset,
                       io_request *user_data) noexcept -> io_uring_result;
    auto prepare_writev(os_fd_t fd, const iovec *iovecs, unsigned nr_vecs, off_t offset,
                        io_request *user_data) noexcept -> io_uring_result;
    auto prepare_close(os_fd_t fd, io_request *user_data) noexcept -> io_uring_result;
    auto prepare_cancel(io_request *cancelling_user_data, io_request *user_data) noexcept -> io_uring_result;
    auto prepare_shutdown(os_fd_t fd, int how, io_request *user_data) noexcept -> io_uring_result;
    auto submit() noexcept -> io_uring_result;
    auto run() noexcept -> void;
};

using io_uring_core_ptr = std::unique_ptr<io_uring_core>;
} // namespace vortex::event
