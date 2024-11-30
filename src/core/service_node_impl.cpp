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

#include "service_node_impl.h"
#include "components_factory_impl.h"
#include "config/config_manager.h"
#include "logger/logger.h"

namespace vortex::core {

service_node_impl::service_node_impl() :
    dispatcher_(std::make_shared<event::io_uring_dispacher_impl>()),
    factory_(std::make_shared<core::components_factory_impl>()) {

    core::logger::info("Service node created. pid: {}", getpid());
}

auto service_node_impl::init() noexcept -> void {
    logger::info("Service node  initialized");

    // init cluster manager

    cluster_manager_ = factory_->create_cluster_manager();
    cluster_manager_->initialize(config_manager_);
    // init health check

    // init metrics

    // init signal handler
}

auto service_node_impl::start() noexcept -> void {
    core::logger::info("Service node started");
    dispatcher_->loop();
}

service_node_impl::~service_node_impl() {
    core::logger::info("Service node destroyed. pid: {}", getpid());
}

} // namespace vortex::core
