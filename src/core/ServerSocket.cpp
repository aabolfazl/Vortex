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

#include "ServerSocket.h"

#include <cmath>

namespace vortex::core {
ServerSocket::ServerSocket(): epoll(std::make_unique<event::EPoll>()) {
}

void ServerSocket::startListening(const uint16_t port, const int backlog) {
    socketFd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFd < 0) {
        throw std::runtime_error("Failed to create socket");
    }

    if (!makeNonBlocking(socketFd)) {
        close(socketFd);
        socketFd = -1;
        throw std::runtime_error("Failed to set socket to non-blocking");
    }

    constexpr int opt = 1;
    if (setsockopt(socketFd, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) < 0) {
        throw std::runtime_error("Failed to set socket options");
    }

    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    if (bind(socketFd, reinterpret_cast<sockaddr *>(&addr), sizeof(addr)) < 0) {
        throw std::runtime_error("Bind failed");
    }

    if (listen(socketFd, backlog) < 0) {
        throw std::runtime_error("Failed to listen on socket");
    }

    epoll->add(socketFd);
    epoll->setEventHandler([this](int fd, uint32_t events) {
        this->onNewEvent(fd, events);
    });
}

void ServerSocket::onNewEvent(const int fd, const uint32_t events) {
    if (fd == socketFd) {
        auto clientFd = acceptConnection();
    } else {
        // read data from client
    }
}

void ServerSocket::eventLoop() const {
    epoll->wait();
}

int ServerSocket::acceptConnection() const {
    sockaddr_in clientAddr = {};
    socklen_t clientLen = sizeof(clientAddr);
    const int clientfd = accept(socketFd, reinterpret_cast<sockaddr *>(&clientAddr), &clientLen);
    if (clientfd < 0) {
        throw std::runtime_error("Accept failed ");
    }

    if (!makeNonBlocking(socketFd)) {
        throw std::runtime_error("Failed to make client socket non-blocking");
    }

    char clientIP[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &clientAddr.sin_addr, clientIP, INET_ADDRSTRLEN);

    return clientfd;
}

bool ServerSocket::makeNonBlocking(const int fd) {
    std::cout << "makeNonBlocking " << fd << std::endl;

    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        std::cerr << "fcntl F_GETFL failed" << std::endl;
        return false;
    }

    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) == -1) {
        std::cerr << "fcntl F_SETFL failed" << std::endl;
        return false;
    }

    return true;
}

ServerSocket::~ServerSocket() {
    if (socketFd != -1) {
        close(socketFd);
    }
}
} // vortex::core
