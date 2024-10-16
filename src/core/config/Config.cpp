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

#include <memory>
#include <string>
#include "Config.h"
#include "iostream"
#include "logger/logger.h"

namespace vortex::core::config {

config_ptr _config = nullptr;

std::string get_string_or_default(const boost::json::object &obj, const std::string &key,
                                  const std::string &default_value = "") {
    if (obj.contains(key)) {
        return obj.at(key).as_string().c_str();
    }
    return default_value;
}

int64_t get_int_or_default(const boost::json::object &obj, const std::string &key, int64_t default_value = 0) {
    if (obj.contains(key)) {
        return obj.at(key).as_int64();
    }
    return default_value;
}

std::unique_ptr<Config> Config::from_json(const boost::json::object &object) {
    auto config_data = std::make_unique<Config>();

    if (object.contains("listener")) {
        const auto &listener_obj = object.at("listener").as_object();
        config_data->listener.port = get_int_or_default(listener_obj, "port", 8080);
    }

    if (object.contains("backends")) {
        const auto &backends_array = object.at("backends").as_array();
        for (const auto &backend_val : backends_array) {
            const auto &backend_obj = backend_val.as_object();
            Backend backend;
            backend.ip = get_string_or_default(backend_obj, "ip", "127.0.0.1");
            backend.port = get_int_or_default(backend_obj, "port", 80);
            backend.weight = get_int_or_default(backend_obj, "weight", 1);

            if (backend_obj.contains("health_check")) {
                const auto &health_check_obj = backend_obj.at("health_check").as_object();
                backend.health_check.interval = get_int_or_default(health_check_obj, "interval", 30);
                backend.health_check.timeout = get_int_or_default(health_check_obj, "timeout", 5);
                backend.health_check.path = get_string_or_default(health_check_obj, "path", "/health");
            }

            config_data->backends.push_back(backend);
        }
    }

    config_data->strategy = get_string_or_default(object, "load_balancing_strategy", "round_robin");

    if (object.contains("logging")) {
        const auto &logging_obj = object.at("logging").as_object();
        config_data->logging.file = get_string_or_default(logging_obj, "file", "/var/log/app.log");
        config_data->logging.level = get_string_or_default(logging_obj, "level", "info");

        if (logging_obj.contains("rotation")) {
            const auto &rotation_obj = logging_obj.at("rotation").as_object();
            config_data->logging.rotation.interval = get_string_or_default(rotation_obj, "interval", "daily");
        }
    }

    if (object.contains("timeouts")) {
        const auto &timeouts_obj = object.at("timeouts").as_object();
        config_data->timeouts.connection = get_int_or_default(timeouts_obj, "connection", 5000);
        config_data->timeouts.read = get_int_or_default(timeouts_obj, "read", 1000);
        config_data->timeouts.write = get_int_or_default(timeouts_obj, "write", 1000);
    }

    if (object.contains("resource_limits")) {
        const auto &resource_limits_obj = object.at("resource_limits").as_object();
        config_data->resource_limits.max_connections = get_int_or_default(resource_limits_obj, "max_connections", 1000);
        config_data->resource_limits.max_files = get_int_or_default(resource_limits_obj, "max_files", 1024);
    }

    if (object.contains("buffers")) {
        const auto &buffers_obj = object.at("buffers").as_object();
        config_data->buffers.read_buffer_size = get_int_or_default(buffers_obj, "read_buffer_size", 4096);
        config_data->buffers.write_buffer_size = get_int_or_default(buffers_obj, "write_buffer_size", 4096);
    }

    return config_data;
}

config_ptr config() {
    if (!_config) {
        throw std::runtime_error("Config is not initialized!");
    }
    return _config;
}
} // namespace vortex::core::config
