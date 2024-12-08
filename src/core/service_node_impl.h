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
#include <mutex>
#include <sys/types.h>
#include <vector>

#include "common/traits.h"
#include "core/config/config_manager.h"
#include "core/io/io_uring_dispacher_impl.h"
#include "vortex/balancer/cluster.h"
#include "vortex/balancer/components_factory.h"
#include "vortex/service_node.h"


namespace vortex::core {
class service_node_impl : service_node {
public:
    explicit service_node_impl();
    virtual ~service_node_impl();
    auto init() noexcept -> void override;
    auto start() noexcept -> void override;

private:
    event::dispatcher_ptr dispatcher_;
    core::componnent_factory_ptr factory_;
    cluster_manager_ptr cluster_manager_;

    bool is_initialized_{false};

    core::config::config_manager& config_manager_ = core::config::config_manager::instance();
};
} // namespace vortex::core
