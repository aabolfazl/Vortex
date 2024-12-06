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
#include "core/interfaces/components_factory.h"
#include "core/interfaces/service_node.h"

namespace vortex::core {
class components_factory_impl : public components_factory {
public:
    auto create_cluster_manager(event::dispatcher_ptr dispatcher) -> cluster_manager_ptr override;
};

} // namespace vortex::core