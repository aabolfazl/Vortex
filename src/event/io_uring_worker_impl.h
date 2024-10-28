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

#include <memory>
#include <netinet/in.h>
#include <stdexcept>
#include "./../core/interfaces/event/io_uring.h"
#include "./../core/interfaces/event/io_uring_core.h"
#include "./../core/interfaces/event/io_uring_worker.h"


namespace vortex::event {
class io_uring_socket;

class io_uring_worker_impl final : public io_uring_worker {
public:
    explicit io_uring_worker_impl();
    ~io_uring_worker_impl() override;

    auto submit_accept_socket(io_uring_socket &socket) const noexcept -> bool override;
    auto submit_connect_request(io_uring_socket &socket, const core::ipv4 &address) noexcept -> io_request* override;
    auto loop() const noexcept -> void override;

    auto handle_completion(const io_uring_cqe *cqe) noexcept -> void override;

private:
    io_uring_core_ptr io_uring_ptr_;
    std::vector<std::pair<std::string, int>> backend_servers_{};
    std::unordered_map<int, int> client_to_backend_map_{};

    void submit() const;
};

} // namespace vortex::event
