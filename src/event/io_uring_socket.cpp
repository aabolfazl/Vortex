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

#include "io_uring_socket.h"

namespace vortex::event {
io_uring_socket::io_uring_socket(const os_fd_t fd, const IoUringSocketType type) : fd(fd), type(type) {}

os_fd_t io_uring_socket::getFd() const {
    return fd;
}

void io_uring_socket::onAccept(io_request* req, const int32_t result) const {
    if (type == IoUringSocketType::Accept && acceptCallback){
        acceptCallback(result);
    }
}

void io_uring_socket::setAcceptCallBack(const AcceptCallback& callback) {
    acceptCallback = callback;
}
}
