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

    auto listeners() const -> const std::vector<listener_t>&;
    auto clusters() const -> const std::vector<cluster_t>&;
    auto load_balancing_strategy() const -> const std::string&;
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
