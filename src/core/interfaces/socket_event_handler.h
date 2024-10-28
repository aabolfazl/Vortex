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

#include <cstdint>
#include <memory>
#include <system_error>

#include "common/traits.h"

namespace vortex::core {
class socket_event_handler{
public:
    virtual ~socket_event_handler() = default;

    virtual auto on_accept(int client_fd, const std::error_code &ec) noexcept -> void = 0;
    virtual auto on_connect(const std::error_code &ec) noexcept -> void = 0;
    virtual auto on_read(const uint8_t *data, size_t length, const std::error_code &ec) noexcept -> void = 0;
    virtual auto on_write(size_t bytes_written, const std::error_code &ec) noexcept -> void = 0;
    virtual auto on_close(const std::error_code &ec) noexcept -> void = 0;
};

using socket_event_handler_ptr = std::shared_ptr<socket_event_handler>;
}
