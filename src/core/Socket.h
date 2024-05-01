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

#ifndef VORTEX_SOCKET_H
#define VORTEX_SOCKET_H

#include <sys/socket.h>
#include <netinet/in.h>

namespace vortex::core {
class Socket {
public:
    explicit Socket();

    ~Socket();

    Socket(Socket &&) noexcept(true) = default;

    Socket &operator=(Socket &&) noexcept(true) = default;

    auto bind(uint16_t port) const -> void;

    auto listen() const -> void;

    auto accept() const -> int;

    auto close() const -> void;

    auto read(uint8_t *buffer, uint64_t len) const -> size_t;

    auto setReuseAddress(bool val) const -> int;

    auto setReusePort(bool val) const -> int;

    auto setNonBlocking() const -> int;

    auto getFd() const -> int;

private:
    int socketFd;
};

}


#endif //VORTEX_SOCKET_H
