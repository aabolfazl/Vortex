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

#include "io_uring.h"

#include <cstdint>
#include <list>
#include <netinet/in.h>

#include "functional"
#include "liburing.h"
#include "memory"

namespace vortex::event {
using accept_callback = std::function<void(int fd)>;

class io_uring_socket {
public:
    virtual ~io_uring_socket() = default;

    auto getFd() const noexcept -> os_fd_t;
    auto close() noexcept -> void;
    auto enableRead() noexcept -> void;
    auto disableRead() noexcept -> void;
    auto enableCloseEvent(bool enable) noexcept -> void;
    auto connect(uint32_t address) noexcept -> void;
    auto write(uint8_t &data) noexcept -> void;
    auto write(const uint8_t *slices, uint64_t num_slice) noexcept -> uint64_t;
    auto shutdown(int how) noexcept -> void;
    auto onAccept(io_request *req, int32_t result) const noexcept -> void;
    auto onConnect(io_request *req, int32_t result) noexcept -> void;
    auto onRead(io_request *req, int32_t result) noexcept -> void;
    auto onWrite(io_request *req, int32_t result) noexcept -> void;
    auto onClose(io_request *req, int32_t result) noexcept -> void;
    auto onCancel(io_request *req, int32_t result) noexcept -> void;
    auto onShutdown(io_request *req, int32_t result) noexcept -> void;
    auto setAcceptCallBack(const accept_callback &callback) noexcept -> void;
    auto getStatus() const noexcept -> io_uring_socket_status;
};
} // namespace vortex::event
