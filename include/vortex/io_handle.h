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

#include <cerrno>
#include <memory>
#include <sys/socket.h>
#include "sys_calls.h"

namespace vortex::core {

class io_result;
class socket_io_handle;

using socket_io_handle_ptr = std::unique_ptr<socket_io_handle>;

class io_handle {
public:
    static socket_io_handle_ptr create_tcp();
    virtual ~io_handle() = default;

    virtual io_result read(void *buffer, size_t length) = 0;
    virtual io_result write(const void *buffer, size_t length) = 0;

    virtual int fd() const = 0;
    virtual void close() = 0;
};
using io_handle_ptr = std::unique_ptr<io_handle>;

class socket_io_handle : public io_handle {
public:
    virtual api::sys_call_result bind(int port) = 0;
    virtual api::sys_call_result listen() = 0;
    virtual api::sys_call_result accept(struct sockaddr *addr, socklen_t *addrlen) = 0;
    virtual api::sys_call_result connect(const struct sockaddr *address, socklen_t len) = 0;

    virtual api::sys_call_result set_socket_option(int level, int optname, const void *optval, socklen_t optlen) = 0;
    virtual api::sys_call_result get_socket_option(int level, int optname, void *optval, socklen_t *optlen) = 0;

    virtual api::sys_call_result set_blocking(bool blocking) = 0;
};

class io_result {
public:
    enum class status {
        OK,
        WOULD_BLOCK,
        REMOTE_CLOSED, // peer closed
        ERROR // system error
    };

    static io_result ok(size_t bytes_transferred) {
        return io_result(status::OK, bytes_transferred, 0);
    }

    static io_result make_would_block() {
        return io_result(status::WOULD_BLOCK, 0, EAGAIN);
    }

    static io_result remote_close() {
        return io_result(status::REMOTE_CLOSED, 0, 0);
    }

    static io_result error(int err) {
        return io_result(status::ERROR, 0, err);
    }

    bool is_ok() const {
        return status_ == status::OK;
    }
    bool would_block() const {
        return status_ == status::WOULD_BLOCK;
    }
    bool remote_closed() const {
        return status_ == status::REMOTE_CLOSED;
    }
    bool is_error() const {
        return status_ == status::ERROR;
    }

    size_t bytes_transferred() const {
        return bytes_transferred_;
    }
    int errorCode() const {
        return error_code_;
    }

private:
    io_result(status status, size_t bytes, int error) : status_(status), bytes_transferred_(bytes), error_code_(error) {
    }

    status status_;
    size_t bytes_transferred_;
    int error_code_;
};
} // namespace vortex::core
