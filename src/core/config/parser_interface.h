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
