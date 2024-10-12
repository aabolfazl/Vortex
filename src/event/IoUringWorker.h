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

#include "io_uring_core.h"
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <netinet/in.h>
#include <memory>

namespace vortex::event {
class io_uring_worker final {
public:
    explicit io_uring_worker();
    ~io_uring_worker();

    io_uring_socket& add_server_socket(os_fd_t fd);
    io_uring_socket& add_client_socket(os_fd_t fd);
    bool submit_accept_socket(io_uring_socket& socket) const;
    io_request* submit_connect_request(io_uring_socket& socket,
                                  const uint8_t& address);
    io_request* submit_read_request(io_uring_socket& socket);
    io_request* submit_write_request(io_uring_socket& socket, const uint8_t& slices);
    io_request* submit_close_request(io_uring_socket& socket);
    io_request* submit_cancel_request(io_uring_socket& socket,
                                 io_request* request_to_cancel);
    io_request* submit_shutdown_request(io_uring_socket& socket, int how);
    uint32_t get_num_of_sockets() const { return _backend_servers.size(); }
    void loop() const;
    void handle_completion(const io_uring_cqe* cqe);

private:
    io_uring_core_ptr _io_uring_ptr;
    std::vector<std::pair<std::string, int>> _backend_servers{};
    std::unordered_map<int, int> _client_to_backend_map{};

    void submit() const;
};

using io_uring_worker_ptr = std::shared_ptr<io_uring_worker>;
}


#endif //IOURINGWORKER_H