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
    const unsigned int numWorkers = getCoresSize();

    for (unsigned int i = 0; i < numWorkers; ++i) {
        const pid_t pid = fork();

        if (pid == -1) {
            std::cerr << "Failed to fork" << std::endl;
        } else if (pid > 0) {
            std::cout << "process " << pid << " started." << std::endl;
            workerProcesses.push_back(pid);
        } else {
            cpu_set_t cpuset;
            CPU_ZERO(&cpuset);
            CPU_SET(i % numWorkers, &cpuset);

            auto childPid = getpid();

            if (sched_setaffinity(0, sizeof(cpu_set_t), &cpuset) == -1) {
                throw std::runtime_error("Failed to set CPU affinity: " + std::string(std::strerror(errno)));
            }

            const char *configPath = getenv("config_file");
            if (configPath == nullptr) {
                throw std::runtime_error("Environment variable 'config_file' is not set");
            }

            const auto worker = WorkerProcess(childPid, configPath);
            worker.start();
        }
    }


    std::cout << "Master waiting for all workers to finish." << std::endl;

    for (const auto pid: workerProcesses) {
        waitpid(pid, nullptr, 0);
    }

    std::cout << "All worker processes finished." << std::endl;
}
} //end core
