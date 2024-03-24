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

#include "Config.h"
#include <memory>

namespace vortex::core::config {
std::shared_ptr<Config> Config::fromJson(boost::json::object &object) {
    auto configData = std::make_shared<Config>();

    auto &listenerObj = object["listener"].as_object();
    configData->listener.port = listenerObj["port"].as_int64();

    auto &backendsArray = object["backends"].as_array();
    for (const auto &backendVal: backendsArray) {
        auto backendObj = backendVal.as_object();
        Backend backend;
        backend.ip = backendObj["ip"].as_string().c_str();
        backend.port = backendObj["port"].as_int64();
        backend.weight = backendObj["weight"].as_int64();

        auto &healthCheckObj = backendObj["health_check"].as_object();
        backend.health_check.interval = healthCheckObj["interval"].as_int64();
        backend.health_check.timeout = healthCheckObj["timeout"].as_int64();
        backend.health_check.path = healthCheckObj["path"].as_string().c_str();

        configData->backends.push_back(backend);
    }

    configData->strategy = object["load_balancing_strategy"].as_string().c_str();

    auto &loggingObj = object["logging"].as_object();
    configData->logging.file = loggingObj["file"].as_string().c_str();
    configData->logging.level = loggingObj["level"].as_string().c_str();
    auto &rotationObj = loggingObj["rotation"].as_object();
    configData->logging.rotation.interval = rotationObj["interval"].as_string().c_str();

    auto &timeoutsObj = object["timeouts"].as_object();
    configData->timeouts.connection = timeoutsObj["connection"].as_int64();
    configData->timeouts.read = timeoutsObj["read"].as_int64();
    configData->timeouts.write = timeoutsObj["write"].as_int64();

    auto &resourceLimitsObj = object["resource_limits"].as_object();
    configData->resource_limits.max_connections = resourceLimitsObj["max_connections"].as_int64();
    configData->resource_limits.max_files = resourceLimitsObj["max_files"].as_int64();

    return configData;
}
}
