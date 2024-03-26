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

#ifndef SERVER_SOCKET_H
#define SERVER_SOCKET_H

#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <memory>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/epoll.h>
#include "Event.h"
#include <config/ConfigLoader.h>

namespace vortex::core {
class ServerSocket final {
public:
    explicit ServerSocket(
        uint16_t readBufferSize,
        uint16_t writeBufferSize,
        int64_t port
    );
    ~ServerSocket();

    auto handleEvent(const Event* event, uint32_t events) const -> void;
    auto startListening(int backlog = SOMAXCONN) -> int;
    auto acceptConnection() const -> int;

    std::function<void(int fd)> onClientAccepted;

private:
    int socketFd{-1};
    uint16_t readBufferSize;
    uint16_t writeBufferSize;
    uint16_t port;

    static auto makeNonBlocking(int fd) -> bool;
    auto onNewEvent(int fd, uint32_t events) const -> void;
};
}
#endif //SERVER_SOCKET_H
