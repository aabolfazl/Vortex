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

#include <string>
#include <vector>
#include <stdint.h>

namespace vortex::core::config {

struct health_check_t {
    int interval;
    int timeout;
    std::string path;
};

enum class load_balancing_strategy_t { round_robin, least_connections, ip_hash };

struct backend_t {
    std::string ip;
    std::string name;
    int port;
    int weight;
    health_check_t health_check;
};

struct cluster_t {
    std::string name;
    std::string desc;
    load_balancing_strategy_t load_balancing_strategy;
    std::vector<backend_t> backends;

    auto load_balancing_strategy_to_string() const -> std::string {
        switch (load_balancing_strategy) {
            case load_balancing_strategy_t::round_robin:
                return "round_robin";
            case load_balancing_strategy_t::least_connections:
                return "least_connections";
            case load_balancing_strategy_t::ip_hash:
                return "ip_hash";
        }
        
        return "unknown";
    }
};

struct listener_t {
    std::string ip;
    int port;
};

struct log_rotation_t {
    std::string interval;
};

struct logging_t {
    std::string file;
    std::string level;
    log_rotation_t rotation;
};

struct security_t {
    std::string ssl_certificate;
    std::string ssl_certificate_key;
};

struct timeouts_t {
    int connection;
    int read;
    int write;
};

struct resource_limits_t {
    int max_connections;
    int max_files;
};

struct buffers_t {
    int read_buffer_size;
    int write_buffer_size;
};

struct worker_t {
    enum class mode { Auto, Fixed };

    mode mode = mode::Auto;
    uint32_t count = 0;
};

struct runtime_t {
    worker_t workers;
};

struct config_t {
    runtime_t runtime;
    std::vector<listener_t> listeners;
    std::vector<cluster_t> clusters;
    logging_t logging;
    security_t security;
    timeouts_t timeouts;
    resource_limits_t resource_limits;
    buffers_t buffers;
};

} // namespace vortex::core::config
