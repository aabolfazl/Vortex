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

namespace vortex::core {

class socket_handle : private traits::non_copyable<socket_handle>, private traits::non_moveable<socket_handle> {
public:
    explicit socket_handle(uint8_t fd) : fd_(fd) {}
    ~socket_handle() {
        if (fd_ >= 0) {
            close(fd_);
        }
    }

    auto get() const-> uint8_t {
        return fd_;
    }

    auto is_valid() const -> bool {
        return fd_ >= 0;
    }

private:
    uint8_t fd_;
};

} // namespace vortex::core
