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

#include "sys_calls_impl.h"
#include <fcntl.h>

namespace vortex::api {
auto sys_calls_impl::create_socket(int domain, int type, int protocol) noexcept -> sys_call_result {
    return sys_call_result::from_return_value(::socket(domain, type, protocol));
}

auto sys_calls_impl::bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) noexcept -> sys_call_result {
    return sys_call_result::from_return_value(::bind(sockfd, addr, addrlen));
}

auto sys_calls_impl::listen(int sockfd, int backlog) noexcept -> sys_call_result {
    return sys_call_result::from_return_value(::listen(sockfd, backlog));
}

auto sys_calls_impl::accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) noexcept -> sys_call_result {
    return sys_call_result::from_return_value(::accept4(sockfd, addr, addrlen, SOCK_NONBLOCK));
}

auto sys_calls_impl::connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) noexcept -> sys_call_result {
    return sys_call_result::from_return_value(::connect(sockfd, addr, addrlen));
}

auto sys_calls_impl::set_socket_option(int sockfd, int level, int optname, const void *optval,
                                       socklen_t optlen) noexcept -> sys_call_result {
    return sys_call_result::from_return_value(::setsockopt(sockfd, level, optname, optval, optlen));
}

auto sys_calls_impl::get_socket_option(int sockfd, int level, int optname, void *optval,
                                       socklen_t *optlen) noexcept -> sys_call_result {
    return sys_call_result::from_return_value(::getsockopt(sockfd, level, optname, optval, optlen));
}

auto sys_calls_impl::set_non_blocking(int sockfd) noexcept -> sys_call_result {
    int flags = ::fcntl(sockfd, F_GETFL, 0);
    if (flags < 0) {
        return sys_call_result::from_return_value(flags);
    }
    return sys_call_result::from_return_value(::fcntl(sockfd, F_SETFL, flags | O_NONBLOCK));
}

auto sys_calls_impl::get_socket_name(int sockfd, struct sockaddr *addr,
                                     socklen_t *addrlen) noexcept -> sys_call_result {
    return sys_call_result::from_return_value(::getsockname(sockfd, addr, addrlen));
}

auto sys_calls_impl::get_peer_name(int sockfd, struct sockaddr *addr, socklen_t *addrlen) noexcept -> sys_call_result {
    return sys_call_result::from_return_value(::getpeername(sockfd, addr, addrlen));
}

auto sys_calls_impl::read(int fd, void *buf, size_t count) noexcept -> sys_call_result {
    return sys_call_result::from_return_value(::read(fd, buf, count));
}

auto sys_calls_impl::write(int fd, const void *buf, size_t count) noexcept -> sys_call_result {
    return sys_call_result::from_return_value(::write(fd, buf, count));
}

auto sys_calls_impl::send(int sockfd, const void *buf, size_t len, int flags) noexcept -> sys_call_result {
    return sys_call_result::from_return_value(::send(sockfd, buf, len, flags));
}

auto sys_calls_impl::recv(int sockfd, void *buf, size_t len, int flags) noexcept -> sys_call_result {
    return sys_call_result::from_return_value(::recv(sockfd, buf, len, flags));
}

auto sys_calls_impl::close(int fd) noexcept -> sys_call_result {
    return sys_call_result::from_return_value(::close(fd));
}

auto sys_calls_impl::shutdown(int sockfd, int how) noexcept -> sys_call_result {
    return sys_call_result::from_return_value(::shutdown(sockfd, how));
}

auto sys_calls_impl::set_blocking(int fd, bool blocking) noexcept -> sys_call_result {
    int flags = ::fcntl(fd, F_GETFL, 0);
    if (flags < 0) {
        return sys_call_result::from_return_value(flags);
    }
    if (blocking) {
        flags &= ~O_NONBLOCK;
    } else {
        flags |= O_NONBLOCK;
    }

    return sys_call_result::from_return_value(::fcntl(fd, F_SETFL, flags));
}
} // namespace vortex::api
