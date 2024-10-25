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

#pragma once

#include <memory>

#include "core/process_manager.h"

namespace vortex {
class vortex_app {
public:
    explicit vortex_app(const std::string &configFile);
    void start();

private:
    std::unique_ptr<core::process_manager> processManager = nullptr;
};
} // vortex