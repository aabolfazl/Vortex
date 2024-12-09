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

namespace vortex::core::network {

class tcp_conn_pool_impl : public tcp_connection_pool {
public:
    explicit tcp_conn_pool_impl(event::dispatcher& dispatcher, ipv4_ptr address, size_t max_connections);
    ~tcp_conn_pool_impl() override;

    auto acquire_connection() noexcept -> op_connection_ref override;
    auto release_connection(client_connection_ptr& connection) noexcept -> void override;

    auto connect_all() const noexcept -> void override;

    auto connections_count() const noexcept -> size_t override;
    auto max_connections() const noexcept -> size_t override;
    auto set_max_connections(size_t max_connections) noexcept -> void override;

    auto set_initilized_callback(initilized_callback callback) noexcept -> void override;

private:
    auto add_connection() noexcept -> void override;

    connections connection_list_;
};

} // namespace vortex::core::network
