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

#include <memory>

namespace vortex::event {
class io_uring_worker {
public:
    virtual ~io_uring_worker() = default;

    // virtual auto add_server_socket(os_fd_t fd) noexcept -> io_uring_socket = 0;
    // virtual auto add_client_socket(os_fd_t fd) noexcept -> io_uring_socket = 0;
    virtual auto submit_accept_socket(io_uring_socket &socket) const noexcept -> bool = 0;
    virtual auto submit_connect_request(io_uring_socket &socket, const core::ipv4 &address) noexcept -> io_request* = 0;
    // virtual auto submit_cancel_request(io_uring_socket &socket, io_request *request_to_cancel) noexcept -> io_request = 0;
    // virtual auto submit_shutdown_request(io_uring_socket &socket, int how) noexcept -> io_request = 0;
    // virtual auto get_num_of_sockets() const noexcept -> uint8_t = 0;
    virtual auto loop() const noexcept -> void = 0;
    virtual auto handle_completion(const io_uring_cqe *cqe) noexcept -> void = 0;
};

using io_uring_worker_ptr = std::shared_ptr<io_uring_worker>;

} // namespace vortex::event
