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
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include "core/logger/logger.h"

namespace vortex::api {

class sys_call_result;

class sys_calls {
public:
    virtual ~sys_calls() = default;

    // Socket operations
    virtual auto create_socket(int domain, int type, int protocol) noexcept -> sys_call_result = 0;
    virtual auto bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) noexcept -> sys_call_result = 0;
    virtual auto listen(int sockfd, int backlog) noexcept -> sys_call_result = 0;
    virtual auto accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) noexcept -> sys_call_result = 0;
    virtual auto connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) noexcept -> sys_call_result = 0;

    // Socket options
    virtual auto set_socket_option(int sockfd, int level, int optname, const void *optval,
                                   socklen_t optlen) noexcept -> sys_call_result = 0;
    virtual auto get_socket_option(int sockfd, int level, int optname, void *optval,
                                   socklen_t *optlen) noexcept -> sys_call_result = 0;
    virtual auto set_non_blocking(int sockfd) noexcept -> sys_call_result = 0;

    // Socket info
    virtual auto get_socket_name(int sockfd, struct sockaddr *addr, socklen_t *addrlen) noexcept -> sys_call_result = 0;
    virtual auto get_peer_name(int sockfd, struct sockaddr *addr, socklen_t *addrlen) noexcept -> sys_call_result = 0;

    // I/O operations
    virtual auto read(int fd, void *buf, size_t count) noexcept -> sys_call_result = 0;
    virtual auto write(int fd, const void *buf, size_t count) noexcept -> sys_call_result = 0;
    virtual auto send(int sockfd, const void *buf, size_t len, int flags) noexcept -> sys_call_result = 0;
    virtual auto recv(int sockfd, void *buf, size_t len, int flags) noexcept -> sys_call_result = 0;

    // Socket lifecycle
    virtual auto close(int fd) noexcept -> sys_call_result = 0;
    virtual auto shutdown(int sockfd, int how) noexcept -> sys_call_result = 0;

    virtual auto set_blocking(int fd, bool blocking) noexcept -> sys_call_result = 0;
};

class sys_call_result {
public:
    static sys_call_result from_return_value(int ret) {
        if (ret >= 0) {
            return sys_call_result(true, ret, 0);
        }
        return sys_call_result(false, ret, errno);
    }

    int result() const {
        return ret_;
    }

    int errnum() const {
        return errno_;
    }
    
    bool succeeded() const {
        return succeeded_;
    }

private:
    sys_call_result(bool succeeded, int ret, int errno_value) : succeeded_(succeeded), ret_(ret), errno_(errno_value) {

    }

    bool succeeded_;
    int ret_;
    int errno_;
};

} // namespace vortex::api
