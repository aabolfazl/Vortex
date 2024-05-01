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
#include "TcpServer.h"

namespace vortex::core {
class WorkerProcess {
public:
    explicit WorkerProcess(pid_t pid, const std::string &configPath);

    ~WorkerProcess();

    void start() const;

private:
    std::unique_ptr<core::TcpServer> server;
    std::shared_ptr<config::ConfigLoader> configLoader;
    std::shared_ptr<event::EventLoop> eventLoop;
};
} // end vortex::core

#endif //WORKERPROCESS_H
