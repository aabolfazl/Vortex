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
#include "core/config/config_manager.h"

#include <functional>
#include <map>
#include <memory>
#include <string>


namespace vortex::core {

using initialized_callback = std::function<void()>;

class backend {
public:
    enum class status { active, inactive };
    enum class type { tcp };
    enum class connection_state { connected, disconnected, connecting, disconnecting };
    enum class health { healthy, unhealthy };

    virtual ~backend() = default;
    // virtual auto get_status() -> status = 0;
    // virtual auto get_type() -> type = 0;
    // virtual auto get_connection_state() -> connection_state = 0;
    // virtual auto get_health() -> health = 0;
    // virtual auto get_name() -> std::string = 0;
    // virtual auto get_weight() -> uint16_t = 0;
    // virtual auto get_max_connections() -> uint16_t = 0;
    // virtual auto get_current_connections() -> uint16_t = 0;

    // virtual auto set_status(status status) -> void = 0;
    // virtual auto set_connection_state(connection_state state) -> void = 0;
    // virtual auto set_health(health health) -> void = 0;
    // virtual auto set_weight(uint16_t weight) -> void = 0;
    // virtual auto set_max_connections(uint16_t max_connections) -> void = 0;
    // virtual auto set_current_connections(uint16_t current_connections) -> void = 0;

    virtual auto connect() -> void = 0;
    virtual auto disconnect() -> void = 0;

    virtual auto on_connect() -> void = 0;
    virtual auto on_disconnect() -> void = 0;
};
using backend_ptr = std::unique_ptr<backend>;

class cluster {
public:
    enum class initialaizign_state { initializing, initialized, failed };

    virtual auto initialize() -> void = 0;
    virtual auto is_initialized() -> bool = 0;
    virtual auto get_name() -> std::string = 0;
    virtual auto get_initialaizign_state() -> initialaizign_state = 0;
    virtual auto set_initialize_callback(initialized_callback callback) -> void = 0;
};
using cluster_ptr = std::unique_ptr<cluster>;


class cluster_manager : traits::non_copyable<cluster_manager>, traits::non_moveable<cluster_manager> {

public:
    virtual auto initialize(config::config_manager&) -> void = 0;
    virtual auto is_initialized() -> bool = 0;
    virtual auto set_initialize_callback(initialized_callback callback) -> void = 0;


    virtual auto add_cluster(cluster_ptr cluster_ptr) -> void = 0;
    virtual auto remove_cluster() -> void = 0;
    virtual auto get_cluster() -> void = 0;

    enum class state {
        // The cluster manager is starting.
        starting,
        // The cluster manager is loading clusters.
        loading_clusters,
        // The cluster manager is waiting for clusters to be initialized.
        waiting_for_clusters,
        // The cluster manager is running.
        running,
        // The cluster manager is shutting down.
        shutting_down,
        // The cluster manager has shut down.
        shuttet_down
    };

    using cluster_map = std::map<std::string, cluster_ptr>;

protected:
    cluster_map clusters_map_;
    std::vector<config::cluster_t> clusters_;

    state state_{state::starting};
};
using cluster_manager_ptr = std::shared_ptr<cluster_manager>;


} // namespace vortex::core
