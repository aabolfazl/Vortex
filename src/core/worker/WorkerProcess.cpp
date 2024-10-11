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

#include "WorkerProcess.h"

#include <iostream>

namespace vortex::core {
WorkerProcess::WorkerProcess(
    const pid_t pid,
    const std::string &configPath
) : configLoader(std::make_unique<config::ConfigLoader>(configPath)),
    eventLoop(std::make_shared<event::IoUringWorker>()) {
    server = std::make_unique<TcpServer>(
        configLoader,
        eventLoop
    );

    std::cout << "WorkerProcess started with " << pid << " id" << std::endl;
}

void WorkerProcess::start() const {
    server->start();
    _exit(0);
}

WorkerProcess::~WorkerProcess() = default;
}
