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

#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <mutex>
#include <sys/types.h>
#include <vector>

#include "common/traits.h"
#include "core/config/config_manager.h"
#include "core/io/io_uring_dispacher_impl.h"


namespace vortex::core {
class service_node : traits::non_copyable<service_node>, traits::non_moveable<service_node> {
public:
    explicit service_node();
    auto init(const core::config::config_manager&) noexcept -> void;
    auto start() noexcept -> void;

private:
    core::config::config_manager* config_manager_;
    event::dispatcher_ptr dispatcher_;
};
} // namespace vortex::core

#endif // PROCESSMANAGER_H
