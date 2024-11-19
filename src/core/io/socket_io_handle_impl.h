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

#include "common/platform.h"
#include "common/sys_calls_impl.h"
#include "common/traits.h"
#include "core/interfaces/io_handle.h"
#include "core/interfaces/sys_calls.h"

namespace vortex::core {

class socket_io_handle_impl : public socket_io_handle,
                              public traits::non_copyable<socket_io_handle_impl>,
                              public traits::non_moveable<socket_io_handle_impl> {

public:
    explicit socket_io_handle_impl(os_fd_t fd);
    ~socket_io_handle_impl() override;

    static socket_io_handle_ptr create_tcp();

    api::sys_call_result bind(int port) override;
    api::sys_call_result listen() override;
    api::sys_call_result accept(struct sockaddr *addr, socklen_t *addrlen) override;
    api::sys_call_result connect(const struct sockaddr *address, socklen_t len) override;

    api::sys_call_result set_socket_option(int level, int optname, const void *optval, socklen_t optlen) override;
    api::sys_call_result get_socket_option(int level, int optname, void *optval, socklen_t *optlen) override;

    io_result read(void *buffer, size_t length) override;
    io_result write(const void *buffer, size_t length) override;


    int fd() const override;
    void close() override;
    api::sys_call_result set_blocking(bool blocking) override;

private:
    os_fd_t fd_ = -1;
    bool close_ = false;
};


} // namespace vortex::core
