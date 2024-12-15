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

#include "backend_impl.h"
#include "core/logger/logger.h"
#include "core/net/tcp_conn_pool_impl.h"

namespace vortex::core {

backend_impl::backend_impl(event::dispatcher& dispatcher, const core::config::backend_t& backend_t,
                           const core::config::resource_limits_t& resource_limits_t) :
    dispatcher_(dispatcher),
    name_(backend_t.name),
    address_(std::make_shared<ipv4>(backend_t.ip, backend_t.port)),
    weight_(backend_t.weight),
    max_connections_(resource_limits_t.max_connections),
    status_(status::inactive),
    type_(type::tcp),
    connection_state_(connection_state::disconnected),
    health_(health::unhealthy) {
    logger::info("Backend created with name: {} and address: {}", name_, address_->to_string());

    // todo: impl in the factory class
    connection_pool_ = std::make_unique<network::tcp_conn_pool_impl>(dispatcher_, address_, max_connections_);
}

backend_impl::~backend_impl() {
    logger::info("Backend destroyed");
}

auto backend_impl::connect() -> void {
    logger::info("Backend connecting...");
    connection_state_ = connection_state::connecting;

    connection_pool_->connect_all();
}

auto backend_impl::disconnect() -> void {
    logger::info("Backend disconnecting...");
    connection_state_ = connection_state::disconnecting;
}

auto backend_impl::on_connect() -> void {
    logger::info("Backend connected");
    connection_state_ = connection_state::connected;
}

auto backend_impl::on_disconnect() -> void {
    logger::info("Backend disconnected");
    connection_state_ = connection_state::disconnected;
}


} // namespace vortex::core
