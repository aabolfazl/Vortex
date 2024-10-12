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

#ifndef VORTEX_IO_URING_H
#define VORTEX_IO_URING_H

#include <cstdint>
#include <list>
#include <netinet/in.h>

#include "functional"
#include "memory"
#include "liburing.h"

namespace vortex::event {
class io_uring_socket;
class io_uring_worker;
class io_request;

enum class IoUringResult { Ok, Error };

struct FileReadyType {
    static constexpr uint32_t Read = 0x1;
    static constexpr uint32_t Write = 0x2;
    static constexpr uint32_t Closed = 0x4;
};

typedef int os_fd_t;

bool is_io_uring_supported();

class io_uring_core {
public:
    explicit io_uring_core(uint32_t io_uring_size);
    ~io_uring_core();

    IoUringResult prepare_accept(io_uring_socket& socket);

    // IoUringResult prepareConnect(os_fd_t fd, const Network::Address::InstanceConstSharedPtr& address,
    // Request* user_data);
    IoUringResult prepare_readv(os_fd_t fd, const iovec* iovecs,
                               unsigned nr_vecs, off_t offset,
                               io_request* user_data);
    IoUringResult prepare_writev(os_fd_t fd, const iovec* iovecs,
                                unsigned nr_vecs,
                                off_t offset, io_request* user_data);
    IoUringResult prepare_close(os_fd_t fd, io_request* user_data);
    IoUringResult prepare_cancel(io_request* cancelling_user_data,
                                io_request* user_data);
    IoUringResult prepare_shutdown(os_fd_t fd, int how, io_request* user_data);
    IoUringResult submit();
    void run();

private:
    ::io_uring ring{};
    std::vector<io_uring_cqe*> cqes;

    sockaddr_in client_addr{};
    socklen_t client_len{};
};

using io_uring_core_ptr = std::unique_ptr<io_uring_core>;

enum IoUringSocketStatus {
    Initialized,
    ReadEnabled,
    ReadDisabled,
    RemoteClosed,
    Closed,
};

using IoUringSocketOnClosedCb = std::function<void(const uint8_t)>;

/**
 * The data returned from the read request.
 */
struct ReadParam {
    //    Buffer::Instance& buf_;
    uint8_t buf_;
    int32_t result_;
};

/**
 * The data returned from the write request.
 */
struct WriteParam {
    int32_t result_;
};

enum class IoUringSocketType {
    Unknown,
    Accept,
    Server,
    Client,
};

using IoUringSocketPtr = std::unique_ptr<io_uring_socket>;

class io_request final {
public:
    enum class RequestType : uint8_t {
        Accept = 0x1,
        Connect = 0x2,
        Read = 0x4,
        Write = 0x8,
        Close = 0x10,
        Cancel = 0x20,
        Shutdown = 0x40,
    };

    io_request(const RequestType type, io_uring_socket& socket) :
        type_(type),
        socket_(socket) {}

    virtual ~io_request() = default;

    RequestType type() const {
        return type_;
    }

    io_uring_socket& socket() const {
        return socket_;
    }

private:
    RequestType type_;
    io_uring_socket& socket_;
};

using FileReadyCb = std::function<uint32_t>;
}

#endif //VORTEX_IO_URING_H
