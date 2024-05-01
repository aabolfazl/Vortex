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
#include "iostream"
#include "EventLoop.h"
#include "EventHandler.h"

namespace vortex::core {

using AcceptCallback = std::function<void(int fd)>;

class ConnectionAcceptor : event::EventInterface {
public:
    explicit ConnectionAcceptor(
        const std::shared_ptr<event::EventLoop> &eventLoop,
        uint16_t port
    );

    ~ConnectionAcceptor();

    ConnectionAcceptor(ConnectionAcceptor &&) noexcept(true) = default;

    ConnectionAcceptor &operator=(ConnectionAcceptor &&) noexcept(true) = default;

    auto setAcceptCallback(const AcceptCallback &callback) -> void;

    auto listen() -> void;

    auto fd() -> int {
        return socket->getFd();
    }

    bool onEvent(const std::any &event) override;

private:
    std::unique_ptr<core::Socket> socket;

    AcceptCallback acceptCallback;

    auto onRead() -> void;
};
}


#endif //VORTEX_CONNECTION_ACCEPTOR_H
