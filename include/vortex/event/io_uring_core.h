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

#include "common/address.h"
#include "io_uring.h"
#include "vortex/event/async_event.h"

namespace vortex::event {

class io_uring_core {
public:
    virtual ~io_uring_core() = default;

    virtual auto prepare_accept(event::accept_operation_ptr ptr) noexcept -> io_uring_result = 0;
    virtual auto prepare_connect(event::connect_operation_ptr op_ptr) noexcept -> io_uring_result = 0;
    virtual auto prepare_recv(event::read_operation_ptr opt_ptr) noexcept -> io_uring_result = 0;

    virtual auto submit() noexcept -> io_uring_result = 0;
    virtual auto run() noexcept -> void = 0;
    virtual auto exit() noexcept -> void = 0;
};

using io_uring_core_ptr = std::unique_ptr<io_uring_core>;
} // namespace vortex::event
