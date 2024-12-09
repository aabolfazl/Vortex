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

#include "client_connection_impl.h"
#include "core/logger/logger.h"

namespace vortex::core::network {
client_connection_impl::client_connection_impl(event::dispatcher& dispatcher, ipv4_ptr address_ptr,
                                               socket_io_handle_ptr&& io_handlr_ptr) noexcept :
    dispatcher_(dispatcher), address_ptr_(address_ptr), io_handle_ptr_(std::move(io_handlr_ptr)) {
}

auto client_connection_impl::connect() -> void {
    core::logger::info("Connect to address {}", address_ptr_->to_string());
    if (state_ == connection_state::opeening) {
        return;
    }

    state_ = connection_state::opeening;

    auto connect_op = std::make_unique<event::connect_operation>(io_handle_ptr_->fd(), address_ptr_, [this](int result)
                                                                 { this->on_connect_result(result); });
    dispatcher_.submit_async_connect(std::move(connect_op));

    logger::info("Connection to address {} submitted", address_ptr_->to_string());
}

auto client_connection_impl::on_connect_result(int result) noexcept -> void {
    core::logger::error("Connect result {}", result);

    if (result == 0) {
        state_ = connection_state::open;
    } else {
        state_ = connection_state::closed;
    }
}

auto client_connection_impl::close() -> void {
    core::logger::info("Close connection to address {}", address_ptr_->to_string());
    if (state_ == connection_state::closed) {
        return;
    }
    state_ = connection_state::closed;
    io_handle_ptr_->close();
}

auto client_connection_impl::dispatcher() -> event::dispatcher& {
    return dispatcher_;
}

auto client_connection_impl::state() const -> connection_state {
    return state_;
}

auto client_connection_impl::id() const -> uint64_t {
    return id_;
}

client_connection_impl::~client_connection_impl() {
    
}


} // namespace vortex::core::network
