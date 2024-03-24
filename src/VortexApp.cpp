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

#include "VortexApp.h"

#include <memory>
#include "memory"
#include "ServerSocket.h"
#include <thread>

namespace vortex {
VortexApp::VortexApp(
    const std::string &configFile
) {
    setenv("config_file", configFile.data(), 1);
}

void VortexApp::start() {
    processManager = std::make_unique<core::ProcessManager>();
    processManager->createWorkers();
}
} // vortex
