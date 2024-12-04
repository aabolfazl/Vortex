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

namespace vortex::core {
backend_impl::backend_impl(event::dispatcher_ptr dispatcher_ptr, const core::config::backend_t &backend_t) :
    dispatcher_(dispatcher_ptr),
    name_(backend_t.name),
    address_(backend_t.ip),
    port_(backend_t.port),
    weight_(backend_t.weight),
    max_connections_(256),
    current_connections_(0),
    status_(status::inactive),
    type_(type::tcp),
    connection_state_(connection_state::disconnected),
    health_(health::unhealthy) {
    logger::info("Backend created with name: {} and address: {} port: {}", name_, address_, port_);
}

backend_impl::~backend_impl() {
    logger::info("Backend destroyed");
}

auto backend_impl::get_status() -> backend::status {
    return status_;
}

auto backend_impl::get_type() -> backend::type {
    return type_;
}

auto backend_impl::get_connection_state() -> backend::connection_state {
    return connection_state_;
}

auto backend_impl::get_health() -> backend::health {
    return health_; 
}

auto backend_impl::get_name() -> std::string {
    return name_;
}

auto backend_impl::get_address() -> std::string {
    return address_;
}

auto backend_impl::get_port() -> uint16_t {
    return port_;
}

auto backend_impl::get_weight() -> uint16_t {
    return weight_;
}

auto backend_impl::get_max_connections() -> uint16_t {
    return max_connections_;
}

auto backend_impl::get_current_connections() -> uint16_t {
    return current_connections_;
}

auto backend_impl::set_status(status status) -> void {
    status_ = status;
}

auto backend_impl::set_connection_state(connection_state state) -> void {
    connection_state_ = state;
}

auto backend_impl::set_health(health health) -> void {
    health_ = health;
}

auto backend_impl::set_weight(uint16_t weight) -> void {
    weight_ = weight;
}

auto backend_impl::set_max_connections(uint16_t max_connections) -> void {
    max_connections_ = max_connections;
}

auto backend_impl::set_current_connections(uint16_t current_connections) -> void {
    current_connections_ = current_connections;
}

auto backend_impl::connect() -> void {
    logger::info("Backend connecting...");
    connection_state_ = connection_state::connecting;
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
