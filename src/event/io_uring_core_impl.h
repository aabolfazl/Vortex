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

#include <cstdint>
#include <netinet/in.h>
#include "memory"
#include "liburing.h"
#include "core/interfaces/event/io_uring.h"
#include "core/interfaces/event/io_uring_core.h"

namespace vortex::event {
class io_uring_socket;
class io_uring_worker_impl;

class io_uring_core_impl final : public io_uring_core {
public:
    explicit io_uring_core_impl(uint32_t io_uring_size);
    ~io_uring_core_impl() override;

    auto prepare_accept(io_uring_socket &socket) noexcept -> io_uring_result override;
    auto prepare_readv(os_fd_t fd, const iovec *iovecs, unsigned nr_vecs, off_t offset,
                       io_request *user_data) noexcept -> io_uring_result override;
    auto prepare_writev(os_fd_t fd, const iovec *iovecs, unsigned nr_vecs, off_t offset,
                        io_request *user_data) noexcept -> io_uring_result override;
    auto prepare_close(os_fd_t fd, io_request *user_data) noexcept -> io_uring_result override;
    auto prepare_cancel(io_request *cancelling_user_data, io_request *user_data) noexcept -> io_uring_result override;
    auto prepare_shutdown(os_fd_t fd, int how, io_request *user_data) noexcept -> io_uring_result override;
    auto submit() noexcept -> io_uring_result override;
    auto run() noexcept -> void override;

private:
    io_uring ring_{};

    sockaddr_in client_addr_{};
    socklen_t client_len_{};
};
}
