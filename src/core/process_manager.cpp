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

#include "process_manager.h"

#include <cerrno>
#include <cstring>
#include <iostream>
#include <sched.h>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>
#include <vector>

#include "config/config_loader.h"
#include "logger/logger.h"

namespace vortex::core {
u_int process_manager::get_cores_size() {
    return std::thread::hardware_concurrency();
}

void process_manager::create_workers() {
    const unsigned int numWorkers = get_cores_size();

    for (unsigned int i = 0; i < numWorkers; ++i) {
        const pid_t pid = fork();

        if (pid == -1) {
            logger::info("Failed to fork");
        } else if (pid > 0) {
            logger::info("process {} started.", pid);
            _worker_processes.push_back(pid);
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

            auto cl = std::make_unique<config::config_loader>(configPath);
        }
    }


    logger::info("Master waiting for all workers to finish.");

    for (const auto pid : _worker_processes) {
        waitpid(pid, nullptr, 0);
    }

    logger::info("All worker processes finished.");
}
} // namespace vortex::core
