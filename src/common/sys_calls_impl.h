
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

#include "vortex/sys_calls.h"

namespace vortex::api {
class sys_calls_impl : public sys_calls {
public:
    static sys_calls_impl &instance() {
        static sys_calls_impl instance;
        return instance;
    }
    
    auto create_socket(int domain, int type, int protocol) noexcept -> sys_call_result override;
    auto bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) noexcept -> sys_call_result override;
    auto listen(int sockfd, int backlog) noexcept -> sys_call_result override; 
    auto accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) noexcept -> sys_call_result override;
    auto connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) noexcept -> sys_call_result override;
    auto set_socket_option(int sockfd, int level, int optname, const void *optval, socklen_t optlen) noexcept -> sys_call_result override;
    auto get_socket_option(int sockfd, int level, int optname, void *optval, socklen_t *optlen) noexcept -> sys_call_result override;
    auto set_non_blocking(int sockfd) noexcept -> sys_call_result override;
    auto get_socket_name(int sockfd, struct sockaddr *addr, socklen_t *addrlen) noexcept -> sys_call_result override;
    auto get_peer_name(int sockfd, struct sockaddr *addr, socklen_t *addrlen) noexcept -> sys_call_result override;
    auto read(int fd, void *buf, size_t count) noexcept -> sys_call_result override;
    auto write(int fd, const void *buf, size_t count) noexcept -> sys_call_result override;
    auto send(int sockfd, const void *buf, size_t len, int flags) noexcept -> sys_call_result override;
    auto recv(int sockfd, void *buf, size_t len, int flags) noexcept -> sys_call_result override;
    auto close(int fd) noexcept -> sys_call_result override;
    auto shutdown(int sockfd, int how) noexcept -> sys_call_result override;
    auto set_blocking(int fd, bool blocking) noexcept -> sys_call_result override;

private:
    sys_calls_impl() = default;
    sys_calls_impl(const sys_calls_impl &) = delete;
    sys_calls_impl &operator=(const sys_calls_impl &) = delete;
};

} // namespace vortex::api
