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

    virtual auto connect_all() noexcept -> void = 0;
    
    virtual auto set_max_connections(size_t max_connections) noexcept -> void = 0;

    virtual auto set_initilized_callback(initilized_callback callback) noexcept -> void = 0;

    virtual auto dispatcher() const noexcept -> event::dispatcher& = 0;

private:
    virtual auto add_connection() noexcept -> void = 0;
};
using tcp_conn_pool_ptr = std::unique_ptr<tcp_connection_pool>;

} // namespace vortex::core::network
