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

#include "connection_acceptor.h"
#include "logger/logger.h"
#include <memory>

#include "event/io_uring_socket_impl.h"

namespace vortex::core {
connection_acceptor::connection_acceptor(
    const event::io_uring_worker_ptr& workerPtr,
    const uint16_t port
) : _socket(std::make_unique<socket>()),
    _io_uring_socket(std::make_unique<event::io_uring_socket_impl>(_socket->get_fd(), event::io_uring_socket_type::accept)) {
    logger::info("connection_acceptor startet on port {}", port);

    _socket->set_reuse_port(true);
    _socket->bind(port);
    _socket->set_non_blocking();
    _socket->listen();

    workerPtr->submit_accept_socket(*_io_uring_socket);
}

void connection_acceptor::setAcceptCallback(const event::accept_callback& callback) const {
    _io_uring_socket->set_accept_call_back(callback);
}

auto connection_acceptor::listen() const -> void {
    _socket->listen();
}

connection_acceptor::~connection_acceptor() {}
}
