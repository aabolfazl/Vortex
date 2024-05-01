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

#include "EventLoop.h"

namespace vortex::event {

EventLoop::EventLoop() {
    std::cerr << "EventLoop()" << std::endl;

    int ret = io_uring_queue_init(32, &ring, 0);
    if (ret < 0) {
        std::cerr << "Failed to initialize io_uring" << std::endl;
    }
}

auto EventLoop::add(EventHandler *handler) -> bool {
    std::cerr << "add()" << std::endl;

    io_uring_sqe *sqe = io_uring_get_sqe(&ring);
    if (!sqe) {
        std::cerr << "Failed to get submission queue entry" << std::endl;
    }

    if (handler->getType() == EVENT_ACCEPT) {
        io_uring_prep_accept(sqe, handler->getFd(), nullptr, nullptr, 0);
    }

    io_uring_sqe_set_data(sqe, reinterpret_cast<void *>(handler));

    if (io_uring_submit(&ring) < 0) {
        std::cerr << "Failed to submit event" << std::endl;
        return false;
    }

    return true;
}


auto EventLoop::loop() -> void {
    std::cerr << "loop started" << std::endl;

    while (true) {
        io_uring_cqe *cqe;
        int ret = io_uring_wait_cqe(&ring, &cqe);
        if (ret < 0) {
            std::cerr << "Error waiting for completion: " << strerror(-ret) << std::endl;
            continue;
        }

        auto cqeGetData = io_uring_cqe_get_data(cqe);
        EventInterface *pEventHandler = static_cast<EventInterface *>(cqeGetData);

        if (cqe->res < 0) {
            std::cerr << "IO operation failed: " << strerror(-cqe->res) << " " << cqe->res << std::endl;
        } else if (cqe->res == 0) {
            std::cout << "EOF or zero bytes written/read" << std::endl;
        } else {
            // accept for now
            std::cout << "Event operation successful" << std::endl;
            pEventHandler->onEvent(cqe->res);
        }

        io_uring_cqe_seen(&ring, cqe);
    }
}

EventLoop::~EventLoop() {
    io_uring_queue_exit(&ring);
}
}

