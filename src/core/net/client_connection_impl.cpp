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
#include "common/error_helper.h"
#include "core/logger/logger.h"

namespace vortex::core::network {
client_connection_impl::client_connection_impl(event::dispatcher& dispatcher, ipv4_ptr address_ptr,
                                               socket_io_handle_ptr&& io_handlr_ptr) noexcept :
    dispatcher_(dispatcher), address_ptr_(address_ptr), io_handle_ptr_(std::move(io_handlr_ptr)) {
}

auto client_connection_impl::connect() -> void {
    LOG_I("Connect to address {}", address_ptr_->to_string());
    if (state_ == connection_state::opeening) {
        return;
    }

    set_state(connection_state::opeening);

    auto connect_op = std::make_unique<event::connect_operation>(io_handle_ptr_->fd(), address_ptr_,
                                                                 [this](int result) { this->on_connect(result); });
    dispatcher_.submit_async_connect(std::move(connect_op));

    LOG_I("Connection to address {} submitted", address_ptr_->to_string());
}

auto client_connection_impl::set_coonecrion_callback(connection_callback& callback) -> void {
    callback_ = &callback;
}

auto client_connection_impl::set_state(connection_state state) -> void {
    LOG_I("Connection fd {} state changed to {}", io_handle_ptr_->fd(), to_string(state));
    state_ = state;

    if (callback_ && state == connection_state::open) {
        callback_->on_event(connection_event::connected);
    } else if (callback_ && state == connection_state::closed) {
        callback_->on_event(connection_event::closed);
    }
}

auto client_connection_impl::on_connect(int result) noexcept -> void {
    LOG_I("Connect result {}", common::get_socket_error(result).data());

    if (result == 0) {
        set_state(connection_state::open);
        enable_read();
    } else {
        set_state(connection_state::closed);
    }
}

auto client_connection_impl::on_connect() noexcept -> void {
    LOG_I("Connection to address {} connected", address_ptr_->to_string());
    set_state(connection_state::open);
}

auto client_connection_impl::enable_read() noexcept -> void {
    LOG_I("Set up read for connection to address {}", address_ptr_->to_string());

    // testing purpose for buffer, we will use buffer pool later
    auto buffer = new char[100];
    auto read_op = std::make_unique<event::recv_operation>(
        io_handle_ptr_->fd(), buffer, 100,
        [this](int result)
        {
            LOG_I("Read operation completed for connection fd {} result {}", io_handle_ptr_->fd(), result);
            if (result <= 0) {
                LOG_E("Connection closed or error, result: {} {}", result, common::get_socket_error(result).data());
                set_state(connection_state::closing);
                io_handle_ptr_->close();
                set_state(connection_state::closed);
            } else {
                LOG_I("Read operation completed with {} bytes", result);
                on_read();
            }
        });
    dispatcher_.submit_async_read(std::move(read_op));
}

auto client_connection_impl::on_read() noexcept -> void {
    LOG_I("Read operation completed for connection fd {}", io_handle_ptr_->fd());
}

auto client_connection_impl::close() -> void {
    LOG_I("Close connection to address {}", address_ptr_->to_string());
    if (state_ == connection_state::closed) {
        return;
    }
    set_state(connection_state::closed);
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
