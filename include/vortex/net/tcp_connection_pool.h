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
#include "vortex/net/connection.h"

#include <functional>
#include <optional>
#include <vector>
#include <memory>

namespace vortex::core::network {

using initilized_callback = std::function<void()>;

using op_connection_ref = std::optional<std::reference_wrapper<client_connection>>;


class tcp_connection_pool : public traits::non_copyable<tcp_connection_pool>,
                            public traits::non_moveable<tcp_connection_pool> {

public:
    virtual ~tcp_connection_pool() = default;
    virtual auto acquire_connection() noexcept -> op_connection_ref = 0;
    virtual auto release_connection(client_connection_ptr& connection) noexcept -> void = 0;

    virtual auto connect_all() const noexcept -> void = 0;

    virtual auto connections_count() const noexcept -> size_t = 0;
    virtual auto max_connections() const noexcept -> size_t = 0;
    virtual auto set_max_connections(size_t max_connections) noexcept -> void = 0;

    virtual auto set_initilized_callback(initilized_callback callback) noexcept -> void = 0;

    using connections = std::vector<client_connection_ptr>;

private:
    virtual auto add_connection() noexcept -> void = 0;
};
using tcp_conn_pool_ptr = std::unique_ptr<tcp_connection_pool>;

} // namespace vortex::core::network
