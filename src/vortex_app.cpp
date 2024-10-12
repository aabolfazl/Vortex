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
#include <thread>

namespace vortex {
vortex_app::vortex_app(
    const std::string &configFile
) {
    setenv("config_file", configFile.data(), 1);
}

void vortex_app::start() {
    processManager = std::make_unique<core::process_manager>();
    processManager->create_workers();
}
} // vortex
