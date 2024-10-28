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

#include "io_uring_socket_factory.h"

#include "io_uring_socket_impl.h"

namespace vortex::event {
io_uring_socket_factory::io_uring_socket_factory(const io_uring_worker_ptr& worker) :
    worker_(worker) {}

io_uring_socket_factory::~io_uring_socket_factory() {}

auto io_uring_socket_factory::create_acceptor(os_fd_t fd) noexcept -> core::async_socket_ptr {
    return std::make_unique<io_uring_socket_impl>(fd, worker_, io_uring_socket_type::accept);
}

auto io_uring_socket_factory::create_connection(os_fd_t fd) noexcept -> core::async_socket_ptr {
    return std::make_unique<io_uring_socket_impl>(fd, worker_, io_uring_socket_type::client);
}
}
