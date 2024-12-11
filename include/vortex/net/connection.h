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

#include "common/traits.h"
#include "vortex/event/dispatcher.h"

#include <chrono>

namespace vortex::core::network {

using ms = std::chrono::milliseconds;
using us = std::chrono::microseconds;

enum class connection_event { connected, closed, error };

class connection_callback{
public:
    virtual ~connection_callback() = default;

   virtual auto on_event(connection_event) -> void = 0;
};

class connection : public traits::non_copyable<connection>, public traits::non_moveable<connection> {
public:
    enum class connection_state { open, opeening, closing, closed };

    virtual ~connection() = default;

    virtual auto close() -> void = 0;
    virtual auto dispatcher() -> event::dispatcher& = 0;

    virtual auto state() const -> connection_state = 0;

    virtual auto id() const -> uint64_t = 0;

    virtual auto set_coonecrion_callback(connection_callback& callback) -> void = 0;
};
using connection_ptr = std::shared_ptr<connection>;

class client_connection : public connection {
public:
    virtual ~client_connection() = default;

    virtual auto connect() -> void = 0;
};
using client_connection_ptr = std::shared_ptr<client_connection>;

} // namespace vortex::core::network
