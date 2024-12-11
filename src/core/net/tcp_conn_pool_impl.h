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

#include "client_connection_impl.h"
#include "common/address.h"
#include "vortex/event/dispatcher.h"
#include "vortex/net/tcp_connection_pool.h"

#include <list>

namespace vortex::core::network {

class tcp_conn_pool_impl;

class tcp_client_impl : public connection_callback {
public:
    explicit tcp_client_impl(tcp_conn_pool_impl& conn_pool, ipv4_ptr address);
    ~tcp_client_impl();

    auto on_event(connection_event event) noexcept -> void override;

private:
    client_connection_ptr connection_;
    tcp_conn_pool_impl& conn_pool_;
};
using tcp_client_ptr = std::unique_ptr<tcp_client_impl>;

class tcp_conn_pool_impl : public tcp_connection_pool {
public:
    explicit tcp_conn_pool_impl(event::dispatcher& dispatcher, ipv4_ptr address, size_t max_connections);
    ~tcp_conn_pool_impl() override;

    auto connect_all() noexcept -> void override;

    auto set_max_connections(size_t max_connections) noexcept -> void override;

    auto set_initilized_callback(initilized_callback callback) noexcept -> void override;

    auto dispatcher() const noexcept -> event::dispatcher& override;
    auto on_coonection_event(tcp_client_impl& client, connection_event event) noexcept -> void;

private:
    auto add_connection() noexcept -> void override;
    auto create_new_client() noexcept -> bool;
    auto increase_active_connections() noexcept -> void;

    event::dispatcher& dispatcher_;
    ipv4_ptr address_;
    size_t max_connections_;

    int active_connections_{0};

    std::list<tcp_client_ptr> connecting_clients_;
    std::list<tcp_client_ptr> ready_clients_;
    std::list<tcp_client_ptr> busy_clients_;
};

} // namespace vortex::core::network
