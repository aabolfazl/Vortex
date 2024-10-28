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

#include "socket.h"
#include "event/io_uring_socket_impl.h"

namespace vortex::core {
connection_acceptor::connection_acceptor(
    const async_socket_factory_ptr &factory,
    const uint16_t port
    ):
    async_socket_factory_(factory),
    acceptor_socket_ptr_(std::make_unique<socket>()) {

    acceptor_socket_ptr_->set_reuse_port(true);
    acceptor_socket_ptr_->bind(port);
    acceptor_socket_ptr_->set_non_blocking();
    acceptor_socket_ptr_->listen();

    acceptor_async_socket_ptr = async_socket_factory_->create_acceptor(acceptor_socket_ptr_->get_fd());

    logger::info("connection_acceptor started on port {}", port);
}

void connection_acceptor::set_accept_callback(const accept_callback &callback) {
    if (acceptor_async_socket_ptr && !acceptor_async_socket_ptr->has_event_handler()) {
        acceptor_async_socket_ptr->set_event_handler(shared_from_this());
    }

    accept_callback_ = callback;
}

auto connection_acceptor::on_accept(const int client_fd, const std::error_code &ec) noexcept -> void {
    if (accept_callback_) {
        accept_callback_(client_fd);
    }
}

void connection_acceptor::start() const {
    if (acceptor_async_socket_ptr) {
        acceptor_async_socket_ptr->start_accept();
    }
}

connection_acceptor::~connection_acceptor() {}
}
