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
#ifndef IOURINGWORKER_H
#define IOURINGWORKER_H
#include <liburing.h>

#include "IoUring.h"

namespace vortex::event {
class IoUringWorker final {
public:
    explicit IoUringWorker();
    IoUringSocket& addServerSocket(os_fd_t fd);
    IoUringSocket& addClientSocket(os_fd_t fd);
    IoUringSocket& addAcceptSocket(os_fd_t fd);
    Request* submitConnectRequest(IoUringSocket& socket,
                                  const uint8_t& address);
    ~IoUringWorker();
    Request* submitReadRequest(IoUringSocket& socket);
    Request* submitWriteRequest(IoUringSocket& socket, const uint8_t& slices);
    Request* submitCloseRequest(IoUringSocket& socket);
    Request* submitCancelRequest(IoUringSocket& socket,
                                 Request* request_to_cancel);
    Request* submitShutdownRequest(IoUringSocket& socket, int how);
    uint32_t getNumOfSockets() const { return backend_servers.size(); }
    void loop();
    void handle_completion(const io_uring_cqe* cqe);

private:
    io_uring ring{};
    std::vector<std::pair<std::string, int>> backend_servers{};
    std::unordered_map<int, int> client_to_backend_map{};
    int listener_fd{};
    char buffer[4096]{};
};
}


#endif //IOURINGWORKER_H