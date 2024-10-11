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

#include "ConnectionAcceptor.h"

#include <iostream>

namespace vortex::core {
ConnectionAcceptor::ConnectionAcceptor(
    const event::IoUringWorkerPtr& workerPtr,
    const uint16_t port
) : socket(std::make_unique<Socket>()),
    ioUringSocket(new event::IoUringSocket(socket->getFd(), event::IoUringSocketType::Accept)) {
    std::cout << "ConnectionAcceptor on port: " << port << std::endl;

    socket->setReusePort(true);
    socket->bind(port);
    socket->setNonBlocking();
    socket->listen();

    workerPtr->submitAcceptSocket(*ioUringSocket);
}

void ConnectionAcceptor::setAcceptCallback(const event::AcceptCallback& callback) const {
    ioUringSocket->setAcceptCallBack(callback);
}

auto ConnectionAcceptor::listen() const -> void {
    socket->listen();
}

ConnectionAcceptor::~ConnectionAcceptor() {}
}
