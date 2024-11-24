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

#include <memory>

#include "core/config/types.h"
#include "core/service_node.h"

namespace vortex {
class vortex_app {
public:
    explicit vortex_app(const std::string& config_path);
    void start();

private:
    auto init_workers(const core::config::worker_t* workers) noexcept -> void;
    auto spawn_workers(uint16_t count) noexcept -> void;
    auto start_service_node() noexcept -> void;

    std::vector<pid_t> nodes_;
    std::string config_path_;
};
} // namespace vortex
