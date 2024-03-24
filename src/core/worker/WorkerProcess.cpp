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
    const std::string &configFile
): pid(pid),
   socket(std::make_unique<ServerSocket>()),
   configLoader(std::make_unique<config::ConfigLoader>(configFile)) {
}

void WorkerProcess::start() const {
    const std::shared_ptr<config::Config> congif = configLoader->load();


    std::cout << "Worker: " << pid << " started with " << congif->strategy << "\n";

    socket->startListening(congif->listener.port);
    socket->eventLoop();

    _exit(0);
}

WorkerProcess::~WorkerProcess() = default;
}
