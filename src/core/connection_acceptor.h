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

#ifndef VORTEX_CONNECTION_ACCEPTOR_H
#define VORTEX_CONNECTION_ACCEPTOR_H

#include "socket.h"
#include <memory>

#include "interfaces/event/io_uring_socket.h"
#include "interfaces/event/io_uring_worker.h"

namespace vortex::core {

class connection_acceptor final {
public:
    explicit connection_acceptor(
        const event::io_uring_worker_ptr& worker_ptr,
        uint16_t port
    );

    ~connection_acceptor();

    connection_acceptor(connection_acceptor&&) noexcept(true) = default;

    connection_acceptor& operator=(connection_acceptor&&) noexcept(true) = default;

    auto setAcceptCallback(const event::accept_callback& callback) const -> void;

    auto listen() const -> void;

    auto fd() const -> int {
        return _socket->get_fd();
    }

private:
    std::unique_ptr<socket> _socket;
    std::unique_ptr<event::io_uring_socket> _io_uring_socket;

    auto onRead() const -> void;
};

using connection_acceptor_ptr = std::unique_ptr<connection_acceptor>;

}


#endif //VORTEX_CONNECTION_ACCEPTOR_H
