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
    const pid_t pid
): pid(pid),
   socket(std::make_unique<ServerSocket>()) {
}

void WorkerProcess::start() const {
    std::cout << "Worker: " << pid << " started" << "\n";
    socket->startListening(8080);
    socket->eventLoop();

    _exit(0);
}

WorkerProcess::~WorkerProcess() = default;
}
