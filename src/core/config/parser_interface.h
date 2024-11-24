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

#include <string>
#include "types.h"

namespace vortex::core::config {

class parser_interface {
public:
    virtual ~parser_interface() = default;
    virtual auto parse(const std::string& filepath) -> config_t = 0;
};

} // namespace vortex::core::config
