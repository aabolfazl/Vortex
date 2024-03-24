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

#ifndef WORKERPROCESS_H
#define WORKERPROCESS_H
#include <memory>
#include <sched.h>

#include "ServerSocket.h"

namespace vortex::core {
class WorkerProcess {
public:
    explicit WorkerProcess(pid_t pid, const std::string &configFile);
    ~WorkerProcess();

    void start() const;

private:
    pid_t pid = {};
    std::unique_ptr<ServerSocket> socket = {};
    std::unique_ptr<config::ConfigLoader> configLoader;
};
} // end vortex::core

#endif //WORKERPROCESS_H
