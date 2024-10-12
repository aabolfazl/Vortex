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

#include "socket.h"
#include <assert.h>
#include <sys/socket.h>
#include <cstring>
#include <csignal>
#include <iostream>
#include "utils.h"
#include "logger/logger.h"

namespace vortex::core {
socket::socket() {
    _socket_fd = ::socket(AF_INET, SOCK_STREAM, 0);
    if (_socket_fd < 0){
        logger::error("Failed to create socket");
        _exit(EXIT_FAILURE);
    }
}

auto socket::bind(uint16_t port) const -> void {
    assert(_socket_fd > 0);
    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (::bind(_socket_fd, reinterpret_cast<sockaddr*>(&addr), sizeof(addr)) < 0){
        logger::error("Bind failed {}", std::string(strerror(errno)));
        close();
        _exit(EXIT_FAILURE);
    }
    logger::info("Bind success on port: ", port);
}

auto socket::listen() const -> void {
    assert(_socket_fd > 0);
    const int ret = ::listen(_socket_fd, SOMAXCONN);
    if (ret < 0){
        _exit(EXIT_FAILURE);
    }
}

auto socket::accept() const -> int {
    assert(_socket_fd > 0);

    sockaddr_in clientAddr = {};
    socklen_t clientLen = sizeof(clientAddr);
    const int peerFd = ::accept(_socket_fd, reinterpret_cast<sockaddr*>(&clientAddr), &clientLen);
    if (peerFd < 0){
        logger::error("accept error");
    }

    return peerFd;
}

auto socket::read(uint8_t* buffer, const uint64_t len) const -> size_t {
    return ::read(_socket_fd, buffer, len);
}

auto socket::set_reuse_address(const bool val) const -> int {
    const int opt = val ? 1 : 0;
    return ::setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);
}

auto socket::set_reuse_port(const bool val) const -> int {
    const int opt = val ? 1 : 0;
    return ::setsockopt(_socket_fd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof opt);
}

auto socket::set_non_blocking() const -> int {
    return make_non_blocking(_socket_fd);
}

auto socket::get_fd() const -> int {
    return _socket_fd;
}

auto socket::close() const -> void {
    if (_socket_fd >= 0){
        ::close(_socket_fd);
    }
}

socket::~socket() {
    close();
}
}
