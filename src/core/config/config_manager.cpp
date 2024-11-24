#include "config_manager.h"
#include <stdexcept>

namespace vortex::core::config {

void config_manager::load(const std::string& filepath, std::unique_ptr<parser_interface> parser) {
    if (!parser) {
        throw std::invalid_argument("Parser cannot be null");
    }
    config_ = parser->parse(filepath);
}

auto config_manager::listeners() const -> const std::vector<listener_t>& {
    return config_.listeners;
}

auto config_manager::clusters() const -> const std::vector<cluster_t>& {
    return config_.clusters;
}

auto config_manager::load_balancing_strategy() const -> const std::string& {
    return config_.load_balancing_strategy;
}

auto config_manager::logging() const -> const logging_t& {
    return config_.logging;
}

auto config_manager::security() const -> const security_t& {
    return config_.security;
}

auto config_manager::timeouts() const -> const timeouts_t& {
    return config_.timeouts;
}

auto config_manager::resource_limits() const -> const resource_limits_t& {
    return config_.resource_limits;
}

auto config_manager::buffers() const -> const buffers_t& {
    return config_.buffers;
}

} // namespace vortex::core::config
