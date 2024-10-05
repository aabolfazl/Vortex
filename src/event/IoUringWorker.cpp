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

#include "IoUringWorker.h"

#include <cstring>
#include <iostream>
#include <stdexcept>

namespace vortex::event {
IoUringWorker::IoUringWorker() {
    if (io_uring_queue_init(256, &ring, 0) < 0) {
        throw std::runtime_error("Failed to initialize io_uring");
    }
}

IoUringSocket& IoUringWorker::addServerSocket(os_fd_t fd) {
}

IoUringSocket& IoUringWorker::addClientSocket(os_fd_t fd) {
}

Request* IoUringWorker::submitConnectRequest(IoUringSocket& socket,
    const uint8_t& address) {
}

IoUringWorker::~IoUringWorker() {
    io_uring_queue_exit(&ring);
}

[[noreturn]] void IoUringWorker::loop() {
    while (true) {
        io_uring_submit_and_wait(&ring, 1);
        io_uring_cqe* cqe;
        unsigned head;
        unsigned count = 0;

        io_uring_for_each_cqe(&ring, head, cqe) {
            handle_completion(cqe);
            ++count;
        }

        io_uring_cq_advance(&ring, count);
    }
}

void IoUringWorker::handle_completion(const io_uring_cqe* cqe) {
    int fd = static_cast<int>(reinterpret_cast<uintptr_t>(
        io_uring_cqe_get_data(cqe)));

    if (cqe->res < 0) {
        std::cerr << "Error on fd " << fd << ": " << strerror(-cqe->res) <<
            std::endl;
        return;
    }

}

}