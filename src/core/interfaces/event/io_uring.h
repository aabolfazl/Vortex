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

#include <cstdint>

#include "functional"
#include "liburing.h"

namespace vortex::event {
class io_uring_socket;
class io_uring_worker_impl;
class io_request;

enum class io_uring_result { success, error };

struct file_ready_type {
    static constexpr uint32_t Read = 0x1;
    static constexpr uint32_t Write = 0x2;
    static constexpr uint32_t Closed = 0x4;
};

typedef int os_fd_t;

bool is_io_uring_supported();

enum io_uring_socket_status {
    initialized,
    read_enabled,
    read_disabled,
    remote_closed,
    closed,
};

enum class io_uring_socket_type {
    unknown,
    accept,
    server,
    client,
};

class io_request final {
public:
    enum class request_type : uint8_t {
        accept = 0x1,
        connect = 0x2,
        Read = 0x4,
        Write = 0x8,
        Close = 0x10,
        Cancel = 0x20,
        Shutdown = 0x40,
    };

    io_request(const request_type type, io_uring_socket &socket) :
        _type(type),
        _socket(socket) {}

    ~io_request() = default;

    request_type type() const {
        return _type;
    }

    io_uring_socket &socket() const {
        return _socket;
    }

private:
    request_type _type;
    io_uring_socket &_socket;
};

using file_ready_cb = std::function<uint32_t>;
} // namespace vortex::event
