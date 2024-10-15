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

#include "worker_process.h"
#include "config/Config.h"
#include "logger/logger.h"
#include <memory>

namespace vortex::core {
worker_process::worker_process(
    const pid_t pid,
    const std::string& configPath
) : _config_loader(std::make_unique<config::ConfigLoader>(configPath)) {
    
    _server = std::make_unique<tcp_server>(_config_loader->load());

    logger::info("WorkerProcess started with {} id", pid);
}

void worker_process::start() const {
    _server->start();
    _exit(0);
}

worker_process::~worker_process() = default;
}
