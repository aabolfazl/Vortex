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

#ifndef VORTEXAPP_H
#define VORTEXAPP_H
#include <memory>

#include "ProcessManager.h"
#include <config/ConfigLoader.h>

namespace vortex {
class VortexApp {
public:
    explicit VortexApp(const std::string &configFile);
    void start();

private:
    std::unique_ptr<core::ProcessManager> processManager = nullptr;
};
} // vortex

#endif //VORTEXAPP_H
