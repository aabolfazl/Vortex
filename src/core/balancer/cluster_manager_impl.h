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

#include "vortex/balancer/cluster.h"
#include "vortex/event/dispatcher.h"

namespace vortex::core {

class cluster_manager_impl final : public cluster_manager {

    /*
     *   ClusterManager is a class that manages the clusters.
     *   It has a map of clusters and can add, remove and get clusters.
     *   It also has an initialize method that initializes the cluster manager.
     *   The cluster manager is responsible for initializing the clusters.
     *
     *   ClusterManager
     *       ├─ Cluster "web_cluster"
     *       │   ├─ Backend1 (with connection pool)
     *       │   └─ Backend2 (with connection pool)
     *       └─ Cluster "api_cluster"
     *           ├─ Backend3 (with connection pool)
     *           └─ Backend4 (with connection pool)
     */

public:
    explicit cluster_manager_impl(event::dispatcher& dispatcher);
    virtual ~cluster_manager_impl();
    auto initialize(config::config_manager&) -> void override;
    auto is_initialized() -> bool override;
    auto set_initialize_callback(initialized_callback callback) -> void override;

    auto add_cluster(cluster_ptr cluster_ptr) -> void override;
    auto remove_cluster() -> void override;
    auto get_cluster() -> void override;

private:
    event::dispatcher& dispatcher_;

    bool initialized_;
    initialized_callback initialize_callback_;
};

} // namespace vortex::core
