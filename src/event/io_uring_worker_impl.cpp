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

#include "io_uring_worker_impl.h"
#include "io_uring_core_impl.h"

namespace vortex::event {
io_uring_worker_impl::io_uring_worker_impl() : io_uring_ptr_(std::make_unique<io_uring_core_impl>(256)) {

}

auto io_uring_worker_impl::submit_accept_socket(io_uring_socket& socket) const noexcept -> bool {
    const auto res = io_uring_ptr_->prepare_accept(socket);

    if (res == io_uring_result::error){
        std::cerr << "Failed to prepare accept request\n";
        return false;
    }

    return true;
}

io_uring_worker_impl::~io_uring_worker_impl() {}

auto io_uring_worker_impl::loop() const noexcept -> void{
    io_uring_ptr_->run();
}

auto io_uring_worker_impl::handle_completion(const io_uring_cqe *cqe) noexcept -> void {

}

void io_uring_worker_impl::submit() const {
    io_uring_ptr_->submit();
}
}
