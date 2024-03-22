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

#include "ProcessManager.h"

#include <iostream>
#include <thread>
#include <unistd.h>
#include <cstring>
#include <sched.h>
#include <iostream>
#include <vector>
#include <thread>
#include <cerrno>
#include <cstring>
#include <sys/wait.h>
#include "worker/WorkerProcess.h"

namespace vortex::core {
u_int ProcessManager::getCoresSize() {
    return std::thread::hardware_concurrency();
}

void ProcessManager::createWorkers() {
    const unsigned int numWorkers = std::thread::hardware_concurrency();

    for (unsigned int i = 0; i < numWorkers; ++i) {
        const pid_t pid = fork();

        if (pid == -1) {
            std::cerr << "Failed to fork" << std::endl;
        } else if (pid > 0) {
            std::cout << "master-> " << pid << std::endl;
            workerProcesses.push_back(pid);
        } else {
            cpu_set_t cpuset;
            CPU_ZERO(&cpuset);
            CPU_SET(i % numWorkers, &cpuset);

            auto childPid = getpid();

            if (sched_setaffinity(0, sizeof(cpu_set_t), &cpuset) == -1) {
                std::cerr << "Failed to set CPU affinity: " << std::strerror(errno) << std::endl;
                _exit(1);
            }

            const auto worker = std::make_unique<WorkerProcess>(childPid);
            worker->start();
        }
    }


    std::cout << "Master waiting for all workers to finish." << std::endl;

    for (const auto pid: workerProcesses) {
        waitpid(pid, nullptr, 0);
    }

    std::cout << "All worker processes finished." << std::endl;
}
} //end core
