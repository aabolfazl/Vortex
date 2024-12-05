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

#include "io_uring_dispacher_impl.h"

namespace vortex::event {

io_uring_dispacher_impl::io_uring_dispacher_impl() : core_(std::make_unique<io_uring_core_impl>(1024)) {
}

io_uring_dispacher_impl::~io_uring_dispacher_impl() {
}

void io_uring_dispacher_impl::submit_async_accept(event::accept_operation_ptr op) {
    core_->prepare_accept(std::move(op));
}

void io_uring_dispacher_impl::submit_async_connect(event::connect_operation_ptr op) {
    core_->prepare_connect(std::move(op));
}

auto io_uring_dispacher_impl::loop() -> void {
    core_->run();
}


} // namespace vortex::event
