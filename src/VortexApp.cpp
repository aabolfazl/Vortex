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
) : loader(std::make_unique<core::config::ConfigLoader>(configFile)) {
}

void VortexApp::start() {
    const std::shared_ptr<core::config::Config> congif = loader->load();

    // test config
    std::cout << congif->backends.at(0).ip << std::endl;

    processManager = std::make_unique<core::ProcessManager>();
    processManager->createWorkers();
}
} // vortex
