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

#include <functional>
#include <memory>
#include <unordered_map>
#include "common/platform.h"
#include "common/traits.h"
#include "core/interfaces/event/async_event.h"

namespace vortex::event {

class dispatcher : public traits::non_copyable<dispatcher>, public traits::non_moveable<dispatcher> {

public:
    virtual ~dispatcher() = default;

    virtual auto submit_async_accept(accept_operation_ptr op) -> void = 0;
    virtual auto submit_async_connect(connect_operation_ptr op) -> void = 0;

    
    virtual auto loop() -> void = 0;

    // virtual auto create_timer(int timeout, const std::function<void()> &callback) -> void;
    // virtual auto post(const std::function<void()> &callback) -> void;
    // virtual auto stop() -> void;
    // virtual auto is_running() -> bool;
};

// struct io_request {
//     request_type type;
//     std::function<void(int result)> callback;
//     os_fd_t fd;
// };

using dispatcher_ptr = std::shared_ptr<dispatcher>;

} // namespace vortex::event
