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

#include "cluster_impl.h"
#include "backend_impl.h"
#include "core/logger/logger.h"

namespace vortex::core {

cluster_impl::cluster_impl(event::dispatcher& dispatcher, const config::cluster_t& cluster_t, const config::resource_limits_t& resource_limits) :
    dispatcher_(dispatcher), name_(cluster_t.name), description_(cluster_t.desc), cluster_t_(cluster_t), resource_limits_(resource_limits) {
    logger::info("Cluster created with name: {} and desc {}", name_, description_);
}

cluster_impl::~cluster_impl() {
    logger::info("Cluster destroyed");
}

auto cluster_impl::initialize() -> void {
    logger::info("Cluster initializing...");

    for (auto& backend_t : cluster_t_.backends) {
        auto backend_ptr = std::make_unique<backend_impl>(dispatcher_, backend_t, resource_limits_);
        backend_ptr->connect();
        backends_.push_back(std::move(backend_ptr));
    }

    // state_ = initialaizign_state::initialized;
    // if (callback_) {
    //     callback_();
    // }
}

auto cluster_impl::is_initialized() -> bool {
    return state_ == initialaizign_state::initialized;
}

auto cluster_impl::get_name() -> std::string {
    return name_;
}

auto cluster_impl::get_initialaizign_state() -> initialaizign_state {
    return state_;
}

auto cluster_impl::set_initialize_callback(initialized_callback callback) -> void {
    callback_ = callback;
}

} // namespace vortex::core
