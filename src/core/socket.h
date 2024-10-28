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

#include <memory>
#include <sys/socket.h>
#include <netinet/in.h>

namespace vortex::core {
class socket {
public:
    explicit socket();

    ~socket();

    socket(socket &&) noexcept(true) = default;

    socket &operator=(socket &&) noexcept(true) = default;

    auto bind(uint16_t port) const -> void;

    auto listen() const -> void;

    auto accept() const -> int;

    auto close() const -> void;

    auto read(uint8_t *buffer, uint64_t len) const -> size_t;

    auto set_reuse_address(bool val) const -> int;

    auto set_reuse_port(bool val) const -> int;

    auto set_non_blocking() const -> int;

    auto get_fd() const -> int;

private:
    int _socket_fd;
};

using socket_ptr = std::unique_ptr<socket>;

}


#endif //VORTEX_SOCKET_H
