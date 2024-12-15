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
#include <map>
#include <memory>
#include <netinet/in.h>
#include <unordered_map>
#include "common/platform.h"
#include "liburing.h"
#include "vortex/event/async_event.h"
#include "vortex/event/io_uring.h"
#include "vortex/event/io_uring_core.h"

namespace vortex::event {
class io_uring_socket;
class io_uring_worker_impl;

using pending_ops_map = std::unordered_map<uint64_t, std::unique_ptr<io_operation>>;

class io_uring_core_impl final : public io_uring_core {
public:
    explicit io_uring_core_impl(uint32_t io_uring_size);
    ~io_uring_core_impl() override;

    // imlemented in new structure
    auto prepare_accept(event::accept_operation_ptr op) noexcept -> io_uring_result override;
    auto prepare_connect(event::connect_operation_ptr op_ptr) noexcept -> io_uring_result override;

    auto prepare_recv(event::recv_operation_ptr opt_ptr) noexcept -> io_uring_result override;

    auto submit() noexcept -> io_uring_result override;
    auto run() noexcept -> void override;
    auto exit() noexcept -> void override;

private:
    io_uring ring_{};
    pending_ops_map pending_ops_;
    uint64_t next_sqe_token_ = 1;

    sockaddr_in client_addr_{};
    socklen_t client_len_{};
};
} // namespace vortex::event
