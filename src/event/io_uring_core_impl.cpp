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

#include <cstring>
#include <iostream>
#include <stdexcept>

#include "../core/logger/logger.h"
#include "io_uring_core_impl.h"


namespace vortex::event {
bool is_io_uring_supported() {
    io_uring ring{};
    if (io_uring_queue_init(1, &ring, 0) == 0) {
        io_uring_queue_exit(&ring);
        return true;
    }
    return false;
}

io_uring_core_impl::io_uring_core_impl(const uint32_t io_uring_size) {
    // int flags = 0;
    // if (use_submission_queue_polling) {
    //     flags |= IORING_SETUP_SQPOLL;
    // }
    // i will iplement this later
    if (io_uring_queue_init(io_uring_size, &ring_, 0) != 0) {
        throw std::runtime_error("Failed to initialize io_uring");
    }
}

io_uring_core_impl::~io_uring_core_impl() {
    core::logger::info("Destroying io_uring core");
    io_uring_queue_exit(&ring_);
}

auto io_uring_core_impl::prepare_accept(event::accept_operation_ptr op) noexcept -> io_uring_result {
    core::logger::info("Prepare accept on socket {}", op->fd);
    if (op->fd <= 0) {
        core::logger::error("Failed to prepare accept on socket {}", op->fd);
        op->complete(-1);
        return io_uring_result::error;
    }

    const auto sqe = io_uring_get_sqe(&ring_);

    if (sqe == nullptr) {
        op->complete(-1);
        return io_uring_result::error;
    }

    io_uring_prep_accept(sqe, op->fd, reinterpret_cast<sockaddr *>(&client_addr_), &client_len_, 0);

    uint64_t token = next_sqe_token_++;
    io_uring_sqe_set_data64(sqe, token);

    pending_ops_[token] = std::move(op);

    return io_uring_result::success;
}

auto io_uring_core_impl::prepare_connect(event::connect_operation_ptr op_ptr) noexcept -> io_uring_result {
    core::logger::info("Prepare connect on socket {} address {} port {}", op_ptr->fd_, op_ptr->address_->to_string(),
                       op_ptr->address_->get_port());
                       
    io_uring_sqe *sqe = io_uring_get_sqe(&ring_);
    if (sqe == nullptr) {
        core::logger::error("Failed to get sqe for connect operation");
        op_ptr->complete(-1);
        return io_uring_result::error;
    }

    io_uring_prep_connect(sqe, op_ptr->fd_, op_ptr->address_->get_sock_addr(), core::ipv4::sock_addr_len());

    uint64_t token = next_sqe_token_++;
    io_uring_sqe_set_data64(sqe, token);

    pending_ops_[token] = std::move(op_ptr);

    return io_uring_result::success;
}

auto io_uring_core_impl::prepare_readv(const os_fd_t fd, const iovec *iovecs, const unsigned nr_vecs,
                                       const off_t offset, io_request *user_data) noexcept -> io_uring_result {
    io_uring_sqe *sqe = io_uring_get_sqe(&ring_);

    if (sqe == nullptr) {
        return io_uring_result::error;
    }

    io_uring_prep_readv(sqe, fd, iovecs, nr_vecs, offset);
    io_uring_sqe_set_data(sqe, user_data);
    return io_uring_result::success;
}

auto io_uring_core_impl::prepare_writev(const os_fd_t fd, const iovec *iovecs, const unsigned nr_vecs,
                                        const off_t offset, io_request *user_data) noexcept -> io_uring_result {
    io_uring_sqe *sqe = io_uring_get_sqe(&ring_);

    if (sqe == nullptr) {
        return io_uring_result::error;
    }

    io_uring_prep_writev(sqe, fd, iovecs, nr_vecs, offset);
    io_uring_sqe_set_data(sqe, user_data);
    return io_uring_result::success;
}

auto io_uring_core_impl::prepare_close(const os_fd_t fd, io_request *user_data) noexcept -> io_uring_result {
    io_uring_sqe *sqe = io_uring_get_sqe(&ring_);

    if (sqe == nullptr) {
        return io_uring_result::error;
    }

    io_uring_prep_close(sqe, fd);
    io_uring_sqe_set_data(sqe, user_data);
    return io_uring_result::success;
}

auto io_uring_core_impl::prepare_cancel(io_request *cancelling_user_data,
                                        io_request *user_data) noexcept -> io_uring_result {
    io_uring_sqe *sqe = io_uring_get_sqe(&ring_);

    if (sqe == nullptr) {
        return io_uring_result::error;
    }

    io_uring_prep_cancel(sqe, cancelling_user_data, 0);
    io_uring_sqe_set_data(sqe, user_data);
    return io_uring_result::success;
}

auto io_uring_core_impl::prepare_shutdown(const os_fd_t fd, const int how,
                                          io_request *user_data) noexcept -> io_uring_result {
    io_uring_sqe *sqe = io_uring_get_sqe(&ring_);

    if (sqe == nullptr) {
        return io_uring_result::error;
    }

    io_uring_prep_shutdown(sqe, fd, how);
    io_uring_sqe_set_data(sqe, user_data);
    return io_uring_result::success;
}

auto io_uring_core_impl::submit() noexcept -> io_uring_result {
    const int ret = io_uring_submit(&ring_);
    if (ret < 0) {
        core::logger::error("io_uring_submit failed ret: {} errno: {}", ret, strerror(errno));
        return io_uring_result::error;
    }

    core::logger::info("io_uring_submit success with submit count of {}", ret);

    return io_uring_result::success;
}

auto io_uring_core_impl::run() noexcept -> void {
    try {
        io_uring_cqe *cqe;

        while (true) {
            io_uring_submit_and_wait(&ring_, 1);

            unsigned cqe_count = 0;
            unsigned head;

            io_uring_for_each_cqe(&ring_, head, cqe) {
                ++cqe_count;

                uint64_t token = io_uring_cqe_get_data64(cqe);
                core::logger::info("Got completion for token {}", token);

                auto it = pending_ops_.find(token);

                if (it == pending_ops_.end()) {
                    core::logger::error("No pending operation found for token {}", token);
                    return;
                }


                if (it != pending_ops_.end()) {
                    if (it->second->type() == operation_type::accept) {
                        auto accept_op =
                            std::unique_ptr<accept_operation>(static_cast<accept_operation *>(it->second.release()));
                        accept_op->complete(cqe->res);
                        prepare_accept(std::move(accept_op));
                    } else {
                        core::logger::info("Completing operation for token {} type {}", token, it->second->type_str());
                        it->second->complete(cqe->res);
                        pending_ops_.erase(it);
                    }
                }
            }

            io_uring_cq_advance(&ring_, cqe_count);
        }
    } catch (const std::exception &e) {
        core::logger::error("Exception while submitting io_uring_submit {}", e.what());
    }
}

auto io_uring_core_impl::exit() noexcept -> void {
    core::logger::info("Exit io_uring_core_impl::exit");
    io_uring_queue_exit(&ring_);

    for (auto &op : pending_ops_) {
        op.second->complete(-1);
    }
}
} // namespace vortex::event
