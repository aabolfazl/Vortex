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


#include "components_factory_impl.h"
#include "core/balancer/cluster_manager_impl.h"


#include <memory>

namespace vortex::core {
auto components_factory_impl::create_cluster_manager() -> cluster_manager_ptr {
    return std::make_shared<cluster_manager_impl>();
}
} // namespace vortex::core
