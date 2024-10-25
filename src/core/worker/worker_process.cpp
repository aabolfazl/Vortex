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

#include <memory>
#include "worker_process.h"

#include "core/logger/logger.h"

namespace vortex::core {

worker_process::worker_process() : _server(std::make_unique<tcp_server>()) {
    logger::info("WorkerProcess started");
}

void worker_process::start() const {
    _server->start();
    _exit(0);
}

worker_process::~worker_process() = default;
} // namespace vortex::core
