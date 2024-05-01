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

namespace vortex::core {

ConnectionAcceptor::ConnectionAcceptor(
    const std::shared_ptr<event::EventLoop> &eventLoop,
    uint16_t port
) : socket(std::make_unique<Socket>()) {
    std::cout << "ConnectionAcceptor on port: " << port << std::endl;

    socket->setReusePort(true);
    socket->bind(port);
    socket->setNonBlocking();
    socket->listen();

    auto event = new event::EventHandler(EVENT_ACCEPT, socket->getFd());
    event->setEventCallback(std::bind(&ConnectionAcceptor::onEvent, this, std::placeholders::_1));

    if (!eventLoop->add(event)) {
        socket->close();
        std::cerr << "Add ConnectionAcceptor failed errno: " + std::string(strerror(errno)) << std::endl;
        _exit(EXIT_FAILURE);
    }
}

void ConnectionAcceptor::setAcceptCallback(const AcceptCallback &callback) {
    ConnectionAcceptor::acceptCallback = callback;
}

auto ConnectionAcceptor::listen() -> void {
    socket->listen();
}

auto ConnectionAcceptor::onRead() -> void {
    auto clientFd = socket->accept();
    if (acceptCallback) {
        acceptCallback(clientFd);
    } else {
        close(clientFd);
    }
}

bool ConnectionAcceptor::onEvent(const std::any &event) {
    if (event.type() == typeid(int)) {
        int num = std::any_cast<int>(event);
        acceptCallback(num);
        return true;
    } else {
        std::cerr << "Event does not contain an int" << std::endl;
        return false;
    }
}

ConnectionAcceptor::~ConnectionAcceptor() {

}
}