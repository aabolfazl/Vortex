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

#pragma once

#include <functional>
#include <memory>
#include "socket.h"

#include "event/io_uring_socket.h"
#include "event/io_uring_worker.h"

namespace vortex::core {

class connection_acceptor {
public:
    virtual ~connection_acceptor() = default;

    connection_acceptor(connection_acceptor &&) noexcept(true) = default;
    connection_acceptor &operator=(connection_acceptor &&) noexcept(true) = default;

    auto setAcceptCallback(const event::accept_callback &callback) const -> void;

    auto listen() const -> void;

    auto fd() const -> uint8_t;
};

using connection_acceptor_ptr = std::unique_ptr<connection_acceptor>;

} // namespace vortex::core
