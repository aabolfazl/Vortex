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

#include "socket_io_handle_impl.h"
#include "core/logger/logger.h"

namespace vortex::core {

socket_io_handle_ptr vortex::core::socket_io_handle_impl::create_tcp() {
    os_fd_t fd = api::sys_calls_impl::instance().create_socket(AF_INET, SOCK_STREAM, 0).result();
    
    if (fd < 0) {
        return nullptr;
    }

    return std::make_unique<socket_io_handle_impl>(fd);
}

socket_io_handle_impl::socket_io_handle_impl(os_fd_t fd = INVALID_SOCKET) : fd_(fd) {
}

socket_io_handle_impl::~socket_io_handle_impl() {
    if (!close_) {
        close();
    }
}

api::sys_call_result socket_io_handle_impl::bind(int port) {
    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(port);

    return api::sys_calls_impl::instance().bind(fd_, (struct sockaddr *) &addr, sizeof(addr));
}

api::sys_call_result socket_io_handle_impl::listen() {
    return api::sys_calls_impl::instance().listen(fd_, SOMAXCONN);
}

int socket_io_handle_impl::fd() const {
    return fd_;
}

api::sys_call_result socket_io_handle_impl::set_blocking(bool blocking) {
    core::logger::info("Setting blocking to {}", blocking);
    return api::sys_calls_impl::instance().set_blocking(fd_, blocking);
}

api::sys_call_result socket_io_handle_impl::accept(struct sockaddr *addr, socklen_t *addrlen) {
    return api::sys_calls_impl::instance().accept(fd_, addr, addrlen);
}

api::sys_call_result socket_io_handle_impl::connect(const struct sockaddr *address, socklen_t len) {
    return api::sys_calls_impl::instance().connect(fd_, address, len);
}

api::sys_call_result socket_io_handle_impl::set_socket_option(int level, int optname, const void *optval,
                                                              socklen_t optlen) {
    return api::sys_calls_impl::instance().set_socket_option(fd_, level, optname, optval, optlen);
}

api::sys_call_result socket_io_handle_impl::get_socket_option(int level, int optname, void *optval, socklen_t *optlen) {
    return api::sys_calls_impl::instance().get_socket_option(fd_, level, optname, optval, optlen);
}

io_result socket_io_handle_impl::read(void *buffer, size_t length) {
    auto res = api::sys_calls_impl::instance().read(fd_, buffer, length);
    if (res.succeeded()) {
        return io_result::ok(res.result());
    }

    if (res.errnum() == EAGAIN || res.errnum() == EWOULDBLOCK) {
        return io_result::make_would_block();
    }

    if (res.errnum() == ECONNRESET) {
        return io_result::remote_close();
    }

    return io_result::error(res.errnum());
}

io_result socket_io_handle_impl::write(const void *buffer, size_t length) {
    auto res = api::sys_calls_impl::instance().write(fd_, buffer, length);
    if (res.succeeded()) {
        return io_result::ok(res.result());
    }

    if (res.errnum() == EAGAIN || res.errnum() == EWOULDBLOCK) {
        return io_result::make_would_block();
    }

    if (res.errnum() == ECONNRESET) {
        return io_result::remote_close();
    }

    return io_result::error(res.errnum());
}


void socket_io_handle_impl::close() {
    if (fd_ != INVALID_SOCKET) {
        api::sys_calls_impl::instance().close(fd_);
        fd_ = INVALID_SOCKET;
        close_ = true;
    }
}

} // namespace vortex::core
