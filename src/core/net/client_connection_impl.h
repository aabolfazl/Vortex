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

#include "vortex/event/dispatcher.h"
#include "vortex/net/connection.h"
#include "vortex/net/io_handle.h"


namespace vortex::core::network {

class client_connection_impl final : public client_connection {
public:
    client_connection_impl(event::dispatcher& dispatcher, ipv4_ptr address_ptr,
                           socket_io_handle_ptr&& io_handlr_ptr) noexcept;

    auto connect() -> void override;

    auto close() -> void override;

    auto dispatcher() -> event::dispatcher& override;

    auto state() const -> connection_state override;

    auto id() const -> uint64_t override;

    ~client_connection_impl() override;

private:
    event::dispatcher& dispatcher_;
    socket_io_handle_ptr io_handle_ptr_;
    ipv4_ptr address_ptr_;
    connection_state state_{connection_state::closed};
    uint64_t id_;

    auto on_connect_result(int result) noexcept -> void;
};

} // namespace vortex::core::network
