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

#include "io_uring_worker.h"

namespace vortex::event {
io_uring_worker::io_uring_worker() : _io_uring_ptr(std::make_unique<io_uring_core>(256)) {}

io_uring_socket& io_uring_worker::add_server_socket(os_fd_t fd) {}

io_uring_socket& io_uring_worker::add_client_socket(os_fd_t fd) {}

bool io_uring_worker::submit_accept_socket(io_uring_socket& socket) const {
    const auto res = _io_uring_ptr->prepare_accept(socket);

    if (res == io_uring_result::error){
        std::cerr << "Failed to prepare accept request\n";
        return false;
    }

    return true;
}

io_request* io_uring_worker::submit_connect_request(io_uring_socket& socket, const uint8_t& address) {}

io_uring_worker::~io_uring_worker() {}

void io_uring_worker::loop() const {
    _io_uring_ptr->run();
}

void io_uring_worker::submit() const {
    _io_uring_ptr->submit();
}

void io_uring_worker::handle_completion(const io_uring_cqe* cqe) {
    const int fd = static_cast<int>(reinterpret_cast<uintptr_t>(io_uring_cqe_get_data(cqe)));

    if (cqe->res < 0){
        std::cerr << "Error on fd " << fd << ": " << strerror(-cqe->res) << std::endl;
        return;
    }
}
}
