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

#include "vortex_app.h"
#include "core/config/config_manager.h"
#include "core/config/yaml_parser.h"
#include "core/logger/logger.h"
#include "core/service_node_impl.h"

#include <cerrno>
#include <cstring>
#include <filesystem>
#include <iostream>
#include <sched.h>
#include <stdlib.h>
#include <string>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>

namespace vortex {
vortex_app::vortex_app(const std::string& config_path) : config_path_(std::move(config_path)) {
    setenv("config_file", config_path_.data(), 1);
    core::config::config_manager::instance();
}

void vortex_app::start() {
    if (config_path_.empty()) {
        core::logger::error("Configuration file is not set");
        exit(EXIT_FAILURE);
        return;
    }

    if (!std::filesystem::exists(config_path_)) {
        core::logger::error("Configuration file does not exist");
        exit(EXIT_FAILURE);
        return;
    }

    auto& config = core::config::config_manager::instance();
    config.load(config_path_, std::make_unique<core::config::yaml_parser>());

    auto workers = config.runtime().workers;
    init_workers(&workers);

    // todo: implement file watcher
    // observe config file changes and send signal to workers
}

auto vortex_app::init_workers(const core::config::worker_t* workers) noexcept -> void {
    if (workers->mode == core::config::worker_t::mode::Auto) {
        core::logger::info("Auto worker mode detected, spawning workers based on CPU count");
        spawn_workers(std::thread::hardware_concurrency());
    } else {
        spawn_workers(workers->count);
    }
}

auto vortex_app::spawn_workers(uint16_t count) noexcept -> void {
    bool need_fork = count > 1;

    if (need_fork) {
        const auto cpu_count = std::thread::hardware_concurrency();
        core::logger::info("Spawning {} workers cpu count {}", count, cpu_count);

        for (unsigned int i = 0; i < count; ++i) {
            pid_t pid = fork();

            if (pid == -1) {
                core::logger::info("Failed to fork");
                start_service_node();
            } else if (pid > 0) {
                nodes_.push_back(pid);
            } else {
                auto child_pid = getpid();

                cpu_set_t cpuset;
                CPU_ZERO(&cpuset);
                CPU_SET(i % cpu_count, &cpuset);

                core::logger::info("Worker {} started with pid {} cpu set to {}", i, child_pid, i % cpu_count);

                if (sched_setaffinity(0, sizeof(cpu_set_t), &cpuset) == -1) {
                    core::logger::error("Failed to set CPU affinity: {}", std::strerror(errno));
                    exit(EXIT_FAILURE);
                }

                start_service_node();
            }
        }

        core::logger::info("Master waiting for all workers to finish.");

        for (const auto pid : nodes_) {
            waitpid(pid, nullptr, 0);
        }

        core::logger::info("All worker processes finished.");
    } else {
        start_service_node();
    }
}


/*
This is a multiproceses method that calls from sepread process, if the worker count is > 1 it will fork and create a new
process for each worker and then call start_service_node method to start the service node if the worker count is 1 it
will call start_service_node method directly this method is called from main process
*/
auto vortex_app::start_service_node() noexcept -> void {
    std::string config_path = std::string(std::getenv("config_file"));
    core::logger::info("start_service_node config_path: {}", config_path);

    if (config_path.empty()) {
        core::logger::error("Environment variable 'config_file' is not set or empty");
        exit(EXIT_FAILURE);
    }

    auto& config_mngr = core::config::config_manager::instance();
    config_mngr.load(config_path, std::make_unique<core::config::yaml_parser>());

    auto app_node = std::make_unique<core::service_node_impl>();
    app_node->init();
    app_node->start();
}

} // namespace vortex
