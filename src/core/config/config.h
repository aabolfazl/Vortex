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

#ifndef CONFIG_H
#define CONFIG_H

#include <cstdint>
#include <memory>
#include <string>
#include <vector>
#include <boost/json.hpp>

namespace vortex::core::config {

struct HealthCheck {
    int64_t interval = 0;
    int64_t timeout = 0;
    std::string path;
};

struct Backend {
    std::string ip;
    int64_t port = 0;
    int64_t weight = 0;
    HealthCheck health_check;
};

struct Listener {
    int64_t port = 0;
};

struct Rotation {
    std::string interval;
};

struct Logging {
    std::string file;
    std::string level;
    Rotation rotation;
};

struct ResourceLimits {
    int64_t max_connections = 0;
    int64_t max_files = 0;
};

struct Timeouts {
    int64_t connection = 0;
    int64_t read = 0;
    int64_t write = 0;
};

struct Buffers {
    int64_t read_buffer_size = 0;
    int64_t write_buffer_size = 0;
};

class config {
public:
    Listener listener;
    std::vector<Backend> backends;
    std::string strategy;
    Logging logging;
    Timeouts timeouts;
    ResourceLimits resource_limits;
    Buffers buffers;

    static std::unique_ptr<config> from_json(const boost::json::object& object);
};

using config_ptr = std::shared_ptr<config>;

extern config_ptr _config;

config_ptr get_config();
}
#endif //CONFIG_H
