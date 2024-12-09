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


#include "tcp_conn_pool_impl.h"
#include "connection_factory_impl.h"
#include "core/io/socket_io_handle_impl.h"
#include "core/logger/logger.h"

namespace vortex::core::network {

tcp_conn_pool_impl::tcp_conn_pool_impl(event::dispatcher& dispatcher, ipv4_ptr address, size_t max_connections) {
    // todo: implement factory registery for all factories
    auto conn_factory = std::make_unique<connection_factory_impl>();

    for (size_t i = 0; i < max_connections; ++i) {
        auto con = conn_factory->create_tcp_connection(dispatcher, address);
        connection_list_.push_back(std::move(con));
        logger::info("Created connection {}", i);
    }

    // start idle connection timer
    // start_idle_connection_timer();

    core::logger::info("Created connection pool with {} connections", max_connections);
}

auto tcp_conn_pool_impl::connect_all() const noexcept -> void {
    for (auto& connection : connection_list_) {
        connection->connect();
    }
}

auto tcp_conn_pool_impl::add_connection() noexcept -> void {
}

auto tcp_conn_pool_impl::acquire_connection() noexcept -> op_connection_ref {
    if (connection_list_.empty()) {
        core::logger::error("No connection available in pool");
        return std::nullopt;
    }
}

auto tcp_conn_pool_impl::release_connection(client_connection_ptr& connection) noexcept -> void {
}

auto tcp_conn_pool_impl::connections_count() const noexcept -> size_t {
    return connection_list_.size();
}

auto tcp_conn_pool_impl::max_connections() const noexcept -> size_t {
    return connection_list_.size();
}

auto tcp_conn_pool_impl::set_max_connections(size_t max_connections) noexcept -> void {
}

auto tcp_conn_pool_impl::set_initilized_callback(initilized_callback callback) noexcept -> void {
}

tcp_conn_pool_impl::~tcp_conn_pool_impl() {
}

} // namespace vortex::core::network
