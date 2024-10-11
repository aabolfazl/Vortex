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

namespace vortex::event {
IoUringWorker::IoUringWorker() : ioUringPtr(std::make_unique<IoUring>(256)) {}

IoUringSocket& IoUringWorker::addServerSocket(os_fd_t fd) {}

IoUringSocket& IoUringWorker::addClientSocket(os_fd_t fd) {}

bool IoUringWorker::submitAcceptSocket(IoUringSocket& socket) const {
    const auto res = ioUringPtr->prepareAccept(socket);

    if (res == IoUringResult::Error){
        std::cerr << "Failed to prepare accept request\n";
        return false;
    }

    return true;
}

Request* IoUringWorker::submitConnectRequest(IoUringSocket& socket, const uint8_t& address) {}

IoUringWorker::~IoUringWorker() {}

void IoUringWorker::loop() {
    do{
        ioUringPtr->run();
    } while (true);
}

void IoUringWorker::submit() const {
    ioUringPtr->submit();
}

void IoUringWorker::handle_completion(const io_uring_cqe* cqe) {
    int fd = static_cast<int>(reinterpret_cast<uintptr_t>(
        io_uring_cqe_get_data(cqe)));

    if (cqe->res < 0){
        std::cerr << "Error on fd " << fd << ": " << strerror(-cqe->res) <<
            std::endl;
        return;
    }
}
}
