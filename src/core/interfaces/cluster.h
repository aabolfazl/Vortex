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

class cluster {

    enum class initialaizign_state { initializing, initialized, failed };

    virtual auto initialize() -> void = 0;
    virtual auto is_initialized() -> bool = 0;
    virtual auto get_name() -> std::string = 0;
    virtual auto get_initialaizign_state() -> initialaizign_state = 0;
    virtual auto set_initialize_callback(initialized_callback callback) -> void = 0;
};
using cluster_ptr = std::shared_ptr<cluster>;


class cluster_manager : traits::non_copyable<cluster_manager>, traits::non_moveable<cluster_manager> {

public:
    virtual auto initialize(config::config_manager&) -> void = 0;
    virtual auto is_initialized() -> bool = 0;
    virtual auto set_initialize_callback(initialized_callback callback) -> void = 0;


    virtual auto add_cluster(cluster_ptr cluster_ptr) -> void = 0;
    virtual auto remove_cluster() -> void = 0;
    virtual auto get_cluster() -> void = 0;

    using cluster_map = std::map<std::string, cluster_ptr>;

private:
    cluster_map clusters;
};
using cluster_manager_ptr = std::shared_ptr<cluster_manager>;

class cluster_manager_factory {
public:
    static auto create_cluster_manager() -> cluster_manager_ptr;
};


} // namespace vortex::core
