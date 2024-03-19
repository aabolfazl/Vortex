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
#include <unistd.h>

namespace vortex::core {
WorkerProcess::WorkerProcess(const pid_t pid): pid(pid) {
}

void WorkerProcess::start() const {
    std::cout << "Worker " << pid << ", sleeping for 10000 ms..." << std::endl;
    usleep(10000 * 1000);
    std::cout << "Worker " << pid << " finished." << std::endl;
    _exit(0);
}

WorkerProcess::~WorkerProcess() = default;
}
