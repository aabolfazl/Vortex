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
#include "vortex/net/tcp_connection_pool.h"

namespace vortex::core {
class backend_impl final : public backend {
public:
    explicit backend_impl(event::dispatcher& dispatcher, const config::backend_t& backend_t,
                          const core::config::resource_limits_t& resource_limits_t);
    virtual ~backend_impl();

    auto connect() -> void override;
    auto disconnect() -> void override;

    auto on_connect() -> void override;
    auto on_disconnect() -> void override;

private:
    event::dispatcher& dispatcher_;
    network::tcp_conn_pool_ptr connection_pool_;
    ipv4_ptr address_;
    std::string name_;
    uint16_t weight_;
    uint16_t max_connections_;
    status status_;
    type type_;
    connection_state connection_state_;
    health health_;
};

} // namespace vortex::core
