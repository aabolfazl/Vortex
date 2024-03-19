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
#include <iostream>
#include <vector>
#include <sys/wait.h>


namespace vortex {
void VortexApp::start() {
    processManager = std::make_unique<core::ProcessManager>();
    processManager->createWorkers();
}
} // vortex
