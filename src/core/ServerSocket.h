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
#include <./../event/EPoll.h>
#include <config/ConfigLoader.h>

namespace vortex::core {
class ServerSocket {
public:
    explicit ServerSocket();

    ~ServerSocket();

    auto startListening(uint16_t port, int backlog = SOMAXCONN) -> void;
    auto eventLoop() const -> void;
    auto acceptConnection() const -> int;

private:
    int socketFd{-1};
    int epollFd{-1};
    std::unique_ptr<event::EPoll> epoll;

    static auto makeNonBlocking(int fd) -> bool;
    auto onNewEvent(int fd, uint32_t events) const -> void;
};
}
#endif //SERVER_SOCKET_H
