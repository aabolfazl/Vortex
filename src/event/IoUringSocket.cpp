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

#include "IoUringSocket.h"

namespace vortex::event {
IoUringSocket::IoUringSocket(const os_fd_t fd, const IoUringSocketType type) : fd(fd), type(type) {}

os_fd_t IoUringSocket::getFd() const {
    return fd;
}

void IoUringSocket::onAccept(Request* req, const int32_t result) const {
    if (type == IoUringSocketType::Accept && acceptCallback){
        acceptCallback(result);
    }
}

void IoUringSocket::setAcceptCallBack(const AcceptCallback& callback) {
    acceptCallback = callback;
}
}
