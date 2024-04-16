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

#include <liburing.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <iostream>

#define PORT 8080
#define BACKLOG 10
#define QUEUE_DEPTH 32

int main() {
    auto ring = io_uring{};
    io_uring_queue_init(QUEUE_DEPTH, &ring, 0);

    int serverFd = socket(AF_INET, SOCK_STREAM | SOCK_NONBLOCK, 0);
    auto addr = sockaddr_in{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);

    if (bind(serverFd, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        std::cerr << "could not bind socket" << std::endl;
        exit(1);
    }

    if (listen(serverFd, BACKLOG) < 0) {
        std::cerr << "could not listen socket" << std::endl;
        exit(1);
    }

    auto *sqe = io_uring_get_sqe(&ring);
    io_uring_prep_accept(sqe, serverFd, nullptr, nullptr, 0);
    io_uring_submit(&ring);

    io_uring_cqe *cqe;
    while (true) {
        io_uring_wait_cqe(&ring, &cqe);
        if (cqe->res >= 0) {
            int clientFd = cqe->res;
            std::cout << "clientFd: " << clientFd << std::endl;
        }

        io_uring_cqe_seen(&ring, cqe);
        std::cout << "accept request : " << std::endl;
    }

    close(serverFd);
    io_uring_queue_exit(&ring);

    return 0;
}