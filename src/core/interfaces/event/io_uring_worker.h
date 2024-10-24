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

#include <cstring>
#include <iostream>
#include <memory>
#include <netinet/in.h>
#include <stdexcept>

namespace vortex::event {
class io_uring_worker {
public:
    virtual ~io_uring_worker() = default;

    auto add_server_socket(os_fd_t fd) noexcept -> io_uring_socket;
    auto add_client_socket(os_fd_t fd) noexcept -> io_uring_socket;
    auto submit_accept_socket(io_uring_socket &socket) const noexcept -> bool;
    auto submit_connect_request(io_uring_socket &socket, const uint8_t &address) noexcept -> io_request;
    auto submit_read_request(io_uring_socket &socket) noexcept -> io_request;
    auto submit_write_request(io_uring_socket &socket, const uint8_t &slices) noexcept -> io_request;
    auto submit_close_request(io_uring_socket &socket) noexcept -> io_request;
    auto submit_cancel_request(io_uring_socket &socket, io_request *request_to_cancel) noexcept -> io_request;
    auto submit_shutdown_request(io_uring_socket &socket, int how) noexcept -> io_request;
    auto get_num_of_sockets() const noexcept -> uint8_t;
    auto loop() const noexcept -> void;
    auto handle_completion(const io_uring_cqe *cqe) noexcept -> void;
};

using io_uring_worker_ptr = std::shared_ptr<io_uring_worker>;

} // namespace vortex::event
