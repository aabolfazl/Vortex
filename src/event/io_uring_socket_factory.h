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

#include "core/interfaces/socket_factory.h"
#include "core/interfaces/event/io_uring_worker.h"

namespace vortex::event {
class io_uring_socket_factory final : public core::async_socket_factory {
public:
    explicit io_uring_socket_factory(const io_uring_worker_ptr& worker);

    ~io_uring_socket_factory() override;
    auto create_acceptor(os_fd_t fd) noexcept -> core::async_socket_ptr override;
    auto create_connection(os_fd_t fd) noexcept -> core::async_socket_ptr override;

private:
    io_uring_worker_ptr worker_;
};
}
