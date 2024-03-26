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

#include "EPoll.h"
#include "ServerSocket.h"

namespace vortex::core {
class WorkerProcess {
public:
    explicit WorkerProcess(pid_t pid, const std::string &configPath);
    ~WorkerProcess();

    void start() const;

private:
    pid_t pid = {};
    std::unique_ptr<ServerSocket> socket = {};
    std::unique_ptr<config::ConfigLoader> configLoader;
    std::unique_ptr<event::EPoll> epoll;

    auto onNewEvent(epoll_event epollEvent) const -> void;
    auto onNewClientConected(int fd) -> void;
};
} // end vortex::core

#endif //WORKERPROCESS_H
