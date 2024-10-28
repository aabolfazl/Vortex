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

#include <memory>

#include "socket.h"
#include "interfaces/async_socket.h"
#include "interfaces/socket_event_handler.h"
#include "interfaces/socket_factory.h"
#include "interfaces/event/io_uring_socket.h"

namespace vortex::core {

class connection_acceptor final : public socket_event_handler, public std::enable_shared_from_this<connection_acceptor> {
public:
    explicit connection_acceptor(
        const async_socket_factory_ptr &factory,
        uint16_t port);

    ~connection_acceptor() override;

    auto set_accept_callback(const accept_callback &callback) -> void;

    auto fd() const -> int {
        return acceptor_async_socket_ptr->get_fd();
    }

    auto on_accept(int client_fd, const std::error_code &ec) noexcept -> void override;
    auto on_connect(const std::error_code &ec) noexcept -> void override {}
    auto on_read(const uint8_t *data, size_t length, const std::error_code &ec) noexcept -> void override {}
    auto on_write(size_t bytes_written, const std::error_code &ec) noexcept -> void override {}
    auto on_close(const std::error_code &ec) noexcept -> void override {}
    void start() const;

private:

    async_socket_factory_ptr async_socket_factory_;
    async_socket_ptr acceptor_async_socket_ptr;
    socket_ptr acceptor_socket_ptr_;

    accept_callback accept_callback_;
};

using connection_acceptor_ptr = std::shared_ptr<connection_acceptor>;

}


#endif //VORTEX_CONNECTION_ACCEPTOR_H
