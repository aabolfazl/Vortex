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

#include "cluster.h"
#include "vortex/event/dispatcher.h"
#include "common/traits.h"

namespace vortex::core {

class components_factory : traits::non_copyable<components_factory>, traits::non_moveable<components_factory> {
public:
    virtual auto create_cluster_manager(event::dispatcher_ptr dispatcher) -> cluster_manager_ptr = 0;
};
using componnent_factory_ptr = std::shared_ptr<components_factory>;

} // namespace vortex::core
