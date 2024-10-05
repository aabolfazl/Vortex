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
#include "functional"
#include "memory"

namespace vortex::event {

class IoUringSocket;
class IoUringWorker;

typedef int os_fd_t;

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
        socket_(socket) {

    }

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