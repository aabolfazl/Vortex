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

#include <iostream>

namespace vortex::core {
worker_process::worker_process(
    const pid_t pid,
    const std::string &configPath
) : _config_loader(std::make_unique<config::ConfigLoader>(configPath)),
    _worker_ptr(std::make_shared<event::io_uring_worker>()) {
    _server = std::make_unique<tcp_server>(
        _config_loader,
        _worker_ptr
    );

    std::cout << "WorkerProcess started with " << pid << " id" << std::endl;
}

void worker_process::start() const {
    _server->start();
    _exit(0);
}

worker_process::~worker_process() = default;
}
