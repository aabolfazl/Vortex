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

#include "IoUring.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

#include "IoUringSocket.h"

namespace vortex::event {
bool isIoUringSupported() {
    io_uring ring;
    if (io_uring_queue_init(1, &ring, 0) == 0){
        io_uring_queue_exit(&ring);
        return true;
    }
    return false;
}

IoUring::IoUring(const uint32_t io_uring_size) {
    // int flags = 0;
    // if (use_submission_queue_polling) {
    //     flags |= IORING_SETUP_SQPOLL;
    // }
    if (io_uring_queue_init(io_uring_size, &ring, 0) != 0){
        throw std::runtime_error("Failed to initialize io_uring");
    }
}

IoUring::~IoUring() {
    io_uring_queue_exit(&ring);
}

IoUringResult IoUring::prepareAccept(IoUringSocket& socket) {
    const auto request = new Request(Request::RequestType::Accept, socket);
    const os_fd_t fd = socket.getFd();

    const auto sqe = io_uring_get_sqe(&ring);

    if (sqe == nullptr){
        return IoUringResult::Error;
    }

    io_uring_prep_accept(sqe, fd, reinterpret_cast<sockaddr*>(&client_addr), &client_len, 0);
    io_uring_sqe_set_data(sqe, request);
    submit();

    return IoUringResult::Ok;
}

// IoUringResult IoUring::prepareConnect(os_fd_t fd,
//                                           const
//                                           Network::Address::InstanceConstSharedPtr
//                                           & address, Request* user_data) {
//     struct io_uring_sqe* sqe = io_uring_get_sqe(&ring_);
//     io_uring_prep_connect(sqe, fd, address->sockAddr(), address->sockAddrLen());
//     io_uring_sqe_set_data(sqe, user_data);
//     return IoUringResult::Ok;
// }

IoUringResult IoUring::prepareReadv(const os_fd_t fd, const iovec* iovecs,
                                    const unsigned nr_vecs, const off_t offset,
                                    Request* user_data) {
    io_uring_sqe* sqe = io_uring_get_sqe(&ring);

    if (sqe == nullptr){
        return IoUringResult::Error;
    }

    io_uring_prep_readv(sqe, fd, iovecs, nr_vecs, offset);
    io_uring_sqe_set_data(sqe, user_data);
    return IoUringResult::Ok;
}

IoUringResult IoUring::prepareWritev(const os_fd_t fd, const iovec* iovecs,
                                     const unsigned nr_vecs, const off_t offset,
                                     Request* user_data) {
    io_uring_sqe* sqe = io_uring_get_sqe(&ring);

    if (sqe == nullptr){
        return IoUringResult::Error;
    }

    io_uring_prep_writev(sqe, fd, iovecs, nr_vecs, offset);
    io_uring_sqe_set_data(sqe, user_data);
    return IoUringResult::Ok;
}

IoUringResult IoUring::prepareClose(const os_fd_t fd, Request* user_data) {
    io_uring_sqe* sqe = io_uring_get_sqe(&ring);

    if (sqe == nullptr){
        return IoUringResult::Error;
    }

    io_uring_prep_close(sqe, fd);
    io_uring_sqe_set_data(sqe, user_data);
    return IoUringResult::Ok;
}

IoUringResult IoUring::prepareCancel(Request* cancelling_user_data, Request* user_data) {
    io_uring_sqe* sqe = io_uring_get_sqe(&ring);

    if (sqe == nullptr){
        return IoUringResult::Error;
    }

    io_uring_prep_cancel(sqe, cancelling_user_data, 0);
    io_uring_sqe_set_data(sqe, user_data);
    return IoUringResult::Ok;
}

IoUringResult IoUring::prepareShutdown(const os_fd_t fd, const int how, Request* user_data) {
    io_uring_sqe* sqe = io_uring_get_sqe(&ring);

    if (sqe == nullptr){
        return IoUringResult::Error;
    }

    io_uring_prep_shutdown(sqe, fd, how);
    io_uring_sqe_set_data(sqe, user_data);
    return IoUringResult::Ok;
}

IoUringResult IoUring::submit() {
    const int ret = io_uring_submit(&ring);
    if (ret < 0){
        return IoUringResult::Error;
    }
    return IoUringResult::Ok;
}

void IoUring::run() {
    io_uring_cqe* cqe;

    while (true){
        constexpr int timeout_ms = 1000;
        __kernel_timespec ts{};
        ts.tv_sec = 0;
        ts.tv_nsec = timeout_ms * 1000000;

        const int ret = io_uring_wait_cqe_timeout(&ring, &cqe, &ts);

        if (ret == 0){
            auto* request = static_cast<Request*>(io_uring_cqe_get_data(cqe));
            if (request){
                switch (request->type()){
                case Request::RequestType::Accept:
                    request->socket().onAccept(request, cqe->res);
                    prepareAccept(request->socket());
                    break;
                default:
                    std::cerr << "Unknown request type\n";
                    break;
                }
            }
            io_uring_cqe_seen(&ring, cqe);
        } else if (ret == -ETIME){
            std::cerr << "ETIME" << "\n";
            continue;
        } else{
            std::cerr << "Error in io_uring_wait_cqe_timeout: " << strerror(-ret) << "\n";
        }
    }
}
}
