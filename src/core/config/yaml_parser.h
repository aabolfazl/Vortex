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

#include <yaml-cpp/yaml.h>
#include "common/traits.h"
#include "parser_interface.h"
#include "types.h"


namespace vortex::core::config {

class yaml_parser : public parser_interface, traits::non_copyable<yaml_parser>, traits::non_moveable<yaml_parser> {
public:
    config_t parse(const std::string& filepath) override;

private:
    auto parse_runtime(const YAML::Node& node) const -> runtime_config_t;
    auto parse_listeners(const YAML::Node& node) const -> std::vector<listener_t>;
    auto parse_clusters(const YAML::Node& node) const -> std::vector<cluster_t>;
    auto parse_logging(const YAML::Node& node) const -> logging_t;
    auto parse_security(const YAML::Node& node) const -> security_t;
    auto parse_timeouts(const YAML::Node& node) const -> timeouts_t;
    auto parse_resource_limits(const YAML::Node& node) const -> resource_limits_t;
    auto parse_buffers(const YAML::Node& node) const -> buffers_t;
};

} // namespace vortex::core::config
