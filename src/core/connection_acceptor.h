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
#include <functional>

#include "io_uring_socket.h"
#include "IoUringWorker.h"

namespace vortex::core {

class connection_acceptor final {
public:
    explicit connection_acceptor(
        const event::io_uring_worker_ptr& workerPtr,
        uint16_t port
    );

    ~connection_acceptor();

    connection_acceptor(connection_acceptor&&) noexcept(true) = default;

    connection_acceptor& operator=(connection_acceptor&&) noexcept(true) = default;

    auto setAcceptCallback(const event::AcceptCallback& callback) const -> void;

    auto listen() const -> void;

    auto fd() const -> int {
        return _socket->get_fd();
    }

private:
    std::unique_ptr<socket> _socket;
    event::io_uring_socket* _io_uring_socket;

    auto onRead() const -> void;
};
}


#endif //VORTEX_CONNECTION_ACCEPTOR_H
