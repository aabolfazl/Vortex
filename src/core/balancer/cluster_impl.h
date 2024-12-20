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

class cluster_impl final : public cluster {
public:
    explicit cluster_impl(event::dispatcher& distpatcher, const config::cluster_t& cluster_t,
                          const config::resource_limits_t& resource_limits);
    virtual ~cluster_impl();
    auto initialize() -> void override;
    auto is_initialized() -> bool override;
    auto get_name() -> std::string override;
    auto get_initialaizign_state() -> initialaizign_state override;
    auto set_initialize_callback(initialized_callback callback) -> void override;

private:
    event::dispatcher& dispatcher_;

    std::string name_;
    std::string description_;
    initialaizign_state state_{initialaizign_state::initializing};
    initialized_callback callback_;

    std::vector<backend_ptr> backends_;
    const config::cluster_t& cluster_t_;
    const config::resource_limits_t resource_limits_;
};

} // namespace vortex::core
