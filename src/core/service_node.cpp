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

#include "service_node.h"

#include "config/config_manager.h"
#include "logger/logger.h"


namespace vortex::core {

service_node::service_node() : dispatcher_(std::make_shared<event::io_uring_dispacher_impl>()) {
    core::logger::info("Service node created. pid: {}", getpid());
}

auto service_node::init(const core::config::config_manager& config_mngr) noexcept -> void {
    logger::info("Service node  initialized");
}

auto service_node::start() noexcept -> void {
    core::logger::info("Service node started");
    dispatcher_->loop();
}

} // namespace vortex::core
