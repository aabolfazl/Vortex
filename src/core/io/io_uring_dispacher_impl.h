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

#include "vortex/event/io_uring.h"
#include "vortex/event/io_uring_core.h"
#include "vortex/event/dispatcher.h"
#include "vortex/event/async_event.h"
#include "event/io_uring_core_impl.h"

namespace vortex::event {

class io_uring_dispacher_impl : public event::dispatcher {

public:
    explicit io_uring_dispacher_impl();
    virtual ~io_uring_dispacher_impl();
    // auto create_network_event() -> event::async_network_event_ptr override;
    auto submit_async_accept(event::accept_operation_ptr op) -> void override;
    auto submit_async_connect(event::connect_operation_ptr op) -> void override;

    auto loop() -> void override;

private:
    io_uring_core_ptr core_;
};
} // namespace vortex::event
