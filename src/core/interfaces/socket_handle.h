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
#include <stdexcept>

#include "common/traits.h"
#include "core/logger/logger.h"
#include "event/io_uring_core.h"

namespace vortex::core {

class socket_handle : traits::non_copyable<socket_handle>, traits::non_moveable<socket_handle> {
public:
    explicit socket_handle(const int fd) :
        fd_(fd) {
        if (fd < 0) {
            throw std::invalid_argument("Invalid file descriptor");
        }
    }

    ~socket_handle() {
        logger::info("Closing socket {}", fd_);
        if (fd_ >= 0) {
            close(fd_);
        }
    }

    auto get() const -> uint8_t {
        return fd_;
    }

    auto is_valid() const -> bool {
        return fd_ >= 0;
    }

private:
    int fd_;
};

} // namespace vortex::core
