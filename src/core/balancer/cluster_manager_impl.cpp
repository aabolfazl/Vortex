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

#include "cluster_manager_impl.h"
#include "cluster_impl.h"
#include "core/config/types.h"
#include "core/logger/logger.h"

namespace vortex::core {

cluster_manager_impl::cluster_manager_impl(event::dispatcher_ptr dispatcher) :
    dispatcher_(dispatcher), initialized_(false) {
    logger::info("Cluster manager created");
}

auto cluster_manager_impl::initialize(config::config_manager& cnfig_mngr) -> void {
    logger::info("Cluster manager initialized");
    initialized_ = true;

    for (const auto& cluster_t : cnfig_mngr.clusters()) {
        clusters_.push_back(cluster_t);

        auto cluster_ptr = std::make_unique<cluster_impl>(dispatcher_, cluster_t);
        cluster_ptr->initialize();
        clusters_map_[cluster_t.name] = std::move(cluster_ptr);
    }
}

auto cluster_manager_impl::is_initialized() -> bool {
    return true;
}

auto cluster_manager_impl::set_initialize_callback(initialized_callback callback) -> void {
    logger::info("Cluster manager set initialize callback");
}

auto cluster_manager_impl::add_cluster(cluster_ptr cluster_ptr) -> void {
    logger::info("Cluster added");
}

auto cluster_manager_impl::remove_cluster() -> void {
    logger::info("Cluster removed");
}

auto cluster_manager_impl::get_cluster() -> void {
    logger::info("Cluster get");
}

cluster_manager_impl::~cluster_manager_impl() {
    logger::info("Cluster manager destroyed");
}

} // namespace vortex::core
