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

#include "core/config/types.h"
#include "vortex/balancer/cluster.h"
#include "vortex/event/dispatcher.h"

namespace vortex::core {
class backend_impl final : public backend {
public:
    explicit backend_impl(event::dispatcher_ptr dispatcher, const config::backend_t& backend_t);
    virtual ~backend_impl();

    auto get_status() -> status override;
    auto get_type() -> type override;
    auto get_connection_state() -> connection_state override;
    auto get_health() -> health override;
    auto get_name() -> std::string override;
    auto get_address() -> std::string override;
    auto get_port() -> uint16_t override;
    auto get_weight() -> uint16_t override;
    auto get_max_connections() -> uint16_t override;
    auto get_current_connections() -> uint16_t override;

    auto set_status(status status) -> void override;
    auto set_connection_state(connection_state state) -> void override;
    auto set_health(health health) -> void override;
    auto set_weight(uint16_t weight) -> void override;
    auto set_max_connections(uint16_t max_connections) -> void override;
    auto set_current_connections(uint16_t current_connections) -> void override;

    auto connect() -> void override;
    auto disconnect() -> void override;

    auto on_connect() -> void override;
    auto on_disconnect() -> void override;

private:
    event::dispatcher_ptr dispatcher_;

    std::string name_;
    std::string address_;
    uint16_t port_;
    uint16_t weight_;
    uint16_t max_connections_;
    uint16_t current_connections_;
    status status_;
    type type_;
    connection_state connection_state_;
    health health_;
};

} // namespace vortex::core
