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

tcp_client_impl::tcp_client_impl(tcp_conn_pool_impl& conn_pool, ipv4_ptr address) :conn_pool_(conn_pool) {
    // todo: implement factory registery for all factories
    auto conn_factory = std::make_unique<connection_factory_impl>();
    auto con = conn_factory->create_tcp_connection(conn_pool.dispatcher(), address);
    connection_ = std::move(con);
    connection_->set_coonecrion_callback(*this);
    connection_->connect();
}

auto tcp_client_impl::on_event(connection_event event) noexcept -> void {
    conn_pool_.on_coonection_event(*this, event);
}

tcp_client_impl::~tcp_client_impl() {}

tcp_conn_pool_impl::tcp_conn_pool_impl(event::dispatcher& dispatcher, ipv4_ptr address, size_t max_connections) :
    dispatcher_(dispatcher), address_(address), max_connections_(max_connections) {

    // start idle connection timer
    // start_idle_connection_timer();

    LOG_I("Created connection pool with {} connections", max_connections);
}

auto tcp_conn_pool_impl::on_coonection_event(tcp_client_impl& client, connection_event event) noexcept -> void {
    LOG_I("Connection event: {}", static_cast<int>(event));
    switch (event) {
    case connection_event::connected:
        core::logger::info("Connection established");
        break;
    case connection_event::closed:
        core::logger::info("Connection closed");
        break;
    case connection_event::error:
        core::logger::error("Connection error");
        break;
    }
}

auto tcp_conn_pool_impl::connect_all() noexcept -> void {
    // testing purpose
    create_new_client();
    create_new_client();
    create_new_client();
    create_new_client();
    create_new_client();
    create_new_client();
    create_new_client();
    create_new_client();
    create_new_client();
    create_new_client();
}

auto tcp_conn_pool_impl::add_connection() noexcept -> void {
}

auto tcp_conn_pool_impl::create_new_client() noexcept -> bool {
    if (active_connections_ > max_connections_) {
        core::logger::warn("Max connections reached max: {} active: {}", max_connections_, active_connections_);
        return false;
    }
    auto client = std::make_unique<tcp_client_impl>(*this, address_);
    connecting_clients_.push_back(std::move(client));
    increase_active_connections();

    return true;
}

auto tcp_conn_pool_impl::set_max_connections(size_t max_connections) noexcept -> void {
}

auto tcp_conn_pool_impl::increase_active_connections() noexcept -> void {
    active_connections_++;
}

auto tcp_conn_pool_impl::set_initilized_callback(initilized_callback callback) noexcept -> void {
}

auto tcp_conn_pool_impl::dispatcher() const noexcept -> event::dispatcher& {
    return dispatcher_;
}

tcp_conn_pool_impl::~tcp_conn_pool_impl() {
}

} // namespace vortex::core::network
