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

#include "Socket.h"
#include <memory>
#include <functional>

#include "IoUringSocket.h"
#include "IoUringWorker.h"

namespace vortex::core {

class ConnectionAcceptor final {
public:
    explicit ConnectionAcceptor(
        const event::IoUringWorkerPtr& workerPtr,
        uint16_t port
    );

    ~ConnectionAcceptor();

    ConnectionAcceptor(ConnectionAcceptor&&) noexcept(true) = default;

    ConnectionAcceptor& operator=(ConnectionAcceptor&&) noexcept(true) = default;

    auto setAcceptCallback(const event::AcceptCallback& callback) const -> void;

    auto listen() const -> void;

    auto fd() const -> int {
        return socket->getFd();
    }

private:
    std::unique_ptr<Socket> socket;
    event::IoUringSocket* ioUringSocket;

    auto onRead() const -> void;
};
}


#endif //VORTEX_CONNECTION_ACCEPTOR_H
