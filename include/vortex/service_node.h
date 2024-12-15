
#pragma once

#include "common/traits.h"
#include "core/config/config_manager.h"
#include "event/dispatcher.h"

namespace vortex::core {
class service_node : traits::non_copyable<service_node>, traits::non_moveable<service_node> {
public:
    virtual ~service_node() = default;
    virtual auto init() noexcept -> void = 0;
    virtual auto start() noexcept -> void = 0;
};
using service_node_ptr = std::shared_ptr<service_node>;

} // namespace vortex::core
