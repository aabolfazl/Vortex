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

#include "core/interfaces/cluster.h"

namespace vortex::core {

class cluster_manager_impl final : public cluster_manager {

public:
    explicit cluster_manager_impl();
    virtual ~cluster_manager_impl();
    auto initialize(config::config_manager&) -> void override;
    auto is_initialized() -> bool override;
    auto set_initialize_callback(initialized_callback callback) -> void override;

    auto add_cluster(cluster_ptr cluster_ptr) -> void override;
    auto remove_cluster() -> void override;
    auto get_cluster() -> void override;

private:
    bool initialized_;
};

} // namespace vortex::core
