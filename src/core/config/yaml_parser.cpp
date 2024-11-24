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

#include "yaml_parser.h"
#include <stdexcept>

namespace vortex::core::config {

config_t yaml_parser::parse(const std::string& filepath) {
    try {
        YAML::Node node = YAML::LoadFile(filepath);
        config_t config;

        if (node["runtime"]) {
            config.runtime = parse_runtime(node["runtime"]);
        }

        if (node["listeners"]) {
            config.listeners = parse_listeners(node["listeners"]);
        }

        if (node["clusters"]) {
            config.clusters = parse_clusters(node["clusters"]);
        }

        if (node["logging"]) {
            config.logging = parse_logging(node["logging"]);
        }

        if (node["timeouts"]) {
            config.timeouts = parse_timeouts(node["timeouts"]);
        }

        if (node["resource_limits"]) {
            config.resource_limits = parse_resource_limits(node["resource_limits"]);
        }

        if (node["buffers"]) {
            config.buffers = parse_buffers(node["buffers"]);
        }

        return config;
    } catch (const std::exception& e) {
        throw std::runtime_error("Failed to parse config: " + std::string(e.what()));
    }
}

auto yaml_parser::parse_runtime(const YAML::Node& node) const -> runtime_config_t {
    runtime_config_t runtime;
    if (node["workers"]) {
        const auto worker_mode_is_auto = node["workers"]["mode"].as<std::string>() == "auto";
        runtime.workers.mode = worker_mode_is_auto ? worker_config_t::mode::Auto : worker_config_t::mode::Fixed;
        runtime.workers.count = worker_mode_is_auto ? 0 : node["workers"]["count"].as<uint32_t>();
    }
    return runtime;
}

auto yaml_parser::parse_listeners(const YAML::Node& node) const -> std::vector<listener_t> {
    std::vector<listener_t> listeners;
    for (const auto& listener_node : node) {
        listener_t listener;
        listener.ip = listener_node["ip"].as<std::string>();
        listener.port = listener_node["port"].as<int>();
        listeners.push_back(std::move(listener));
    }

    return listeners;
}

auto yaml_parser::parse_clusters(const YAML::Node& node) const -> std::vector<cluster_t> {
    std::vector<cluster_t> clusters;

    for (const auto& cluster_node : node) {
        cluster_t cluster;
        cluster.name = cluster_node["name"].as<std::string>();
        if (cluster_node["description"]) {
            cluster.desc = cluster_node["description"].as<std::string>();
        }

        const auto& strategy = cluster_node["load_balancing_strategy"].as<std::string>();

        if (strategy == "round_robin") {
            cluster.load_balancing_strategy = load_balancing_strategy_t::round_robin;
        } else if (strategy == "least_connections") {
            cluster.load_balancing_strategy = load_balancing_strategy_t::least_connections;
        } else if (strategy == "ip_hash") {
            cluster.load_balancing_strategy = load_balancing_strategy_t::ip_hash;
        } else {
            throw std::runtime_error("Invalid load balancing strategy: " + strategy);
        }

        for (const auto& backend_node : cluster_node["backends"]) {
            backend_t backend;
            backend.ip = backend_node["ip"].as<std::string>();
            backend.port = backend_node["port"].as<int>();
            backend.weight = backend_node["weight"].as<int>();

            if (backend_node["name"]) {
                backend.name = backend_node["name"].as<std::string>();
            }

            auto health_check_node = backend_node["health_check"];
            backend.health_check.interval = health_check_node["interval"].as<int>();
            backend.health_check.timeout = health_check_node["timeout"].as<int>();
            backend.health_check.path = health_check_node["path"].as<std::string>();

            cluster.backends.push_back(std::move(backend));
        }

        clusters.push_back(std::move(cluster));
    }


    return clusters;
}

auto yaml_parser::parse_logging(const YAML::Node& node) const -> logging_t {
    logging_t logging;
    logging.file = node["file"].as<std::string>();
    logging.level = node["level"].as<std::string>();
    logging.rotation.interval = node["rotation"]["interval"].as<std::string>();
    return logging;
}

auto yaml_parser::parse_security(const YAML::Node& node) const -> security_t {
    security_t security;
    security.ssl_certificate = node["ssl_certificate"].as<std::string>();
    security.ssl_certificate_key = node["ssl_certificate_key"].as<std::string>();
    return security;
}

auto yaml_parser::parse_timeouts(const YAML::Node& node) const -> timeouts_t {
    timeouts_t timeouts;
    timeouts.connection = node["connection"].as<int>();
    timeouts.read = node["read"].as<int>();
    timeouts.write = node["write"].as<int>();
    return timeouts;
}

auto yaml_parser::parse_resource_limits(const YAML::Node& node) const -> resource_limits_t {
    resource_limits_t limits;
    limits.max_connections = node["max_connections"].as<int>();
    limits.max_files = node["max_files"].as<int>();
    return limits;
}

auto yaml_parser::parse_buffers(const YAML::Node& node) const -> buffers_t {
    buffers_t buffers;
    buffers.read_buffer_size = node["read_buffer_size"].as<int>();
    buffers.write_buffer_size = node["write_buffer_size"].as<int>();
    return buffers;
}

} // namespace vortex::core::config
