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

#include "Socket.h"
#include <assert.h>
#include <sys/socket.h>
#include <cstring>
#include <csignal>
#include <iostream>
#include "utils.h"

namespace vortex::core {

Socket::Socket() {
    std::cerr << "Socket()" << std::endl;
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd < 0) {
        std::cerr << "Failed to create socket" << std::endl;
        _exit(EXIT_FAILURE);
    }
}

auto Socket::bind(uint16_t port) const -> void {
    assert(socketFd > 0);
    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (::bind(socketFd, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0) {
        std::cerr << "Bind failed " + std::string(strerror(errno)) << std::endl;
        close();
        _exit(EXIT_FAILURE);
    }
    std::cerr << "Bind success on port: " << port << std::endl;
}

auto Socket::listen() const -> void {
    assert(socketFd > 0);
   const int ret = ::listen(socketFd, SOMAXCONN);
    if (ret < 0) {
        _exit(EXIT_FAILURE);
    }
}

auto Socket::accept() const -> int {
    assert(socketFd > 0);

    sockaddr_in clientAddr = {};
    socklen_t clientLen = sizeof(clientAddr);
    const int peerFd = ::accept(socketFd, reinterpret_cast<sockaddr *>(&clientAddr), &clientLen);
    if (peerFd < 0) {
        std::cerr << "accept error" << std::endl;
    }

    return peerFd;
}

auto Socket::read(uint8_t *buffer, const uint64_t len) const -> size_t {
    return ::read(socketFd, buffer, len);
}

auto Socket::setReuseAddress(const bool val) const -> int {
    const int opt = val ? 1 : 0;
    return ::setsockopt(socketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);
}

auto Socket::setReusePort(const bool val) const -> int {
    const int opt = val ? 1 : 0;
    return ::setsockopt(socketFd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof opt);
}

auto Socket::setNonBlocking() const -> int {
    return makeNonBlocking(socketFd);
}

auto Socket::getFd() const -> int {
    return socketFd;
}

auto Socket::close() const -> void {
    if (socketFd >= 0) {
        ::close(socketFd);
    }
}

Socket::~Socket() {
    close();
}

}
