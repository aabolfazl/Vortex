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

#include "core/logger/logger.h"

namespace vortex::event {
io_uring_socket_impl::io_uring_socket_impl(
    const os_fd_t fd,
    const io_uring_worker_ptr &worker,
    const io_uring_socket_type type
    ) :
    socket_handle_(fd),
    type_(type),
    worker_(worker) {

    core::logger::info("Creating io_uring_socket_impl {}", fd);
}

io_uring_socket_impl::~io_uring_socket_impl() {
    core::logger::info("Destroying io_uring_socket_impl {}", socket_handle_.get());
}

auto io_uring_socket_impl::get_fd() const noexcept -> os_fd_t {
    return socket_handle_.get();
}

void io_uring_socket_impl::set_event_handler(std::shared_ptr<core::socket_event_handler> handler) noexcept {
    event_handler_ = std::move(handler);
    _has_event_handler = event_handler_ != nullptr;
}

auto io_uring_socket_impl::has_event_handler() const noexcept -> bool { return _has_event_handler; }

auto io_uring_socket_impl::on_accept(io_request *req, const int32_t result) const noexcept -> void {
    core::logger::info("on_accept() {}", result);
    if (event_handler_) {
        std::error_code ec;
        if (result < 0) {
            ec = std::error_code(-result, std::system_category());
        }
        event_handler_->on_accept(result, ec);
    }
}

auto io_uring_socket_impl::on_connect(io_request *req, int32_t result) noexcept -> void {
    core::logger::info("on_connect() {}", result);
}

auto io_uring_socket_impl::on_read(io_request *req, int32_t result) noexcept -> void {}
auto io_uring_socket_impl::on_write(io_request *req, int32_t result) noexcept -> void {}
auto io_uring_socket_impl::on_close(io_request *req, int32_t result) noexcept -> void {}
auto io_uring_socket_impl::on_cancel(io_request *req, int32_t result) noexcept -> void {}
auto io_uring_socket_impl::on_shutdown(io_request *req, int32_t result) noexcept -> void {}

auto io_uring_socket_impl::get_status() const noexcept -> io_uring_socket_status { return status_; }

void io_uring_socket_impl::start_accept() noexcept {
    worker_->submit_accept_socket(*this);
}

void io_uring_socket_impl::connect(core::ipv4 address) noexcept {}

void io_uring_socket_impl::start_read() noexcept {}

void io_uring_socket_impl::start_write(const uint8_t *data, size_t length) noexcept {}

void io_uring_socket_impl::close() noexcept {}

void io_uring_socket_impl::shutdown(int how) noexcept {}
}
