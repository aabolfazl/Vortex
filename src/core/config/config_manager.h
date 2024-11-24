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
#include "common/traits.h"
#include "parser_interface.h"
#include "types.h"

namespace vortex::core::config {

class config_manager : traits::non_copyable<config_manager>, traits::non_moveable<config_manager> {
public:
    static config_manager& instance() {
        static config_manager instance;
        return instance;
    }

    void load(const std::string& filepath, std::unique_ptr<parser_interface> parser);

    auto runtime() const -> const runtime_t&;
    auto listeners() const -> const std::vector<listener_t>&;
    auto clusters() const -> const std::vector<cluster_t>&;
    auto logging() const -> const logging_t&;
    auto security() const -> const security_t&;
    auto timeouts() const -> const timeouts_t&;
    auto resource_limits() const -> const resource_limits_t&;
    auto buffers() const -> const buffers_t&;

private:
    config_manager() = default;
    ~config_manager() = default;
    config_manager(const config_manager&) = delete;
    config_manager& operator=(const config_manager&) = delete;

    config_t config_;
};
} // namespace vortex::core::config
