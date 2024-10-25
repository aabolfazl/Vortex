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

#include "io_uring_socket_impl.h"

namespace vortex::event {
io_uring_socket_impl::io_uring_socket_impl(const os_fd_t fd, const io_uring_socket_type type) :
    socket_handle_(fd),
    type_(type) {}

auto io_uring_socket_impl::get_fd() const noexcept -> os_fd_t {
    return socket_handle_.get();
}

auto io_uring_socket_impl::close() noexcept -> void {}
auto io_uring_socket_impl::enable_read() noexcept -> void {}
auto io_uring_socket_impl::disabler_read() noexcept -> void {}
auto io_uring_socket_impl::enable_close_event(bool enable) noexcept -> void {}
auto io_uring_socket_impl::connect(uint32_t address) noexcept -> void {}
auto io_uring_socket_impl::write(uint8_t &data) noexcept -> void {}
auto io_uring_socket_impl::write(const uint8_t *slices, uint64_t num_slice) noexcept -> uint64_t {}
auto io_uring_socket_impl::shutdown(int how) noexcept -> void {}


auto io_uring_socket_impl::on_accept(io_request *req, const int32_t result) const noexcept -> void {
    if (type_ == io_uring_socket_type::accept && accept_callback_) {
        accept_callback_(result);
    }
}

auto io_uring_socket_impl::on_connect(io_request *req, int32_t result) noexcept -> void {}
auto io_uring_socket_impl::on_read(io_request *req, int32_t result) noexcept -> void {}
auto io_uring_socket_impl::on_write(io_request *req, int32_t result) noexcept -> void {}
auto io_uring_socket_impl::on_close(io_request *req, int32_t result) noexcept -> void {}
auto io_uring_socket_impl::on_cancel(io_request *req, int32_t result) noexcept -> void {}
auto io_uring_socket_impl::on_shutdown(io_request *req, int32_t result) noexcept -> void {}

auto io_uring_socket_impl::set_accept_call_back(const accept_callback &callback) noexcept -> void {
    accept_callback_ = callback;
}

auto io_uring_socket_impl::get_status() const noexcept -> io_uring_socket_status { return status_; }
}
