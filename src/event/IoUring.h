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
class IoUringSocket;
class IoUringWorker;
class Request;

enum class IoUringResult { Ok, Error };

struct FileReadyType {
    static constexpr uint32_t Read = 0x1;
    static constexpr uint32_t Write = 0x2;
    static constexpr uint32_t Closed = 0x4;
};

typedef int os_fd_t;

bool isIoUringSupported();

class IoUring {
public:
    explicit IoUring(uint32_t io_uring_size);
    ~IoUring();

    IoUringResult prepareAccept(IoUringSocket& socket);

    // IoUringResult prepareConnect(os_fd_t fd, const Network::Address::InstanceConstSharedPtr& address,
    // Request* user_data);
    IoUringResult prepareReadv(os_fd_t fd, const iovec* iovecs,
                               unsigned nr_vecs, off_t offset,
                               Request* user_data);
    IoUringResult prepareWritev(os_fd_t fd, const iovec* iovecs,
                                unsigned nr_vecs,
                                off_t offset, Request* user_data);
    IoUringResult prepareClose(os_fd_t fd, Request* user_data);
    IoUringResult prepareCancel(Request* cancelling_user_data,
                                Request* user_data);
    IoUringResult prepareShutdown(os_fd_t fd, int how, Request* user_data);
    IoUringResult submit();
    void injectCompletion(os_fd_t fd, Request* user_data, int32_t result);
    void removeInjectedCompletion(os_fd_t fd);
    void run();

private:
    io_uring ring{};
    std::vector<io_uring_cqe*> cqes;

    sockaddr_in client_addr{};
    socklen_t client_len{};
};

using IoUringPtr = std::unique_ptr<IoUring>;

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

using IoUringSocketPtr = std::unique_ptr<IoUringSocket>;

class Request final {
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

    Request(const RequestType type, IoUringSocket& socket) :
        type_(type),
        socket_(socket) {}

    virtual ~Request() = default;

    RequestType type() const {
        return type_;
    }

    IoUringSocket& socket() const {
        return socket_;
    }

private:
    RequestType type_;
    IoUringSocket& socket_;
};

using FileReadyCb = std::function<uint32_t>;
}

#endif //VORTEX_IO_URING_H
