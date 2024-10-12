//
// Created by abolfazl on 10/5/24.
//

#ifndef IOURINGSOCKET_H
#define IOURINGSOCKET_H
#include "io_uring_core.h"

namespace vortex::event {
using AcceptCallback = std::function<void(int fd)>;


class io_uring_socket final {
public:
    explicit io_uring_socket(os_fd_t fd, IoUringSocketType type);
    ~io_uring_socket() = default;

    os_fd_t getFd() const;

    void close(bool keep_fd_open, IoUringSocketOnClosedCb cb = nullptr);
    void enableRead();
    void disableRead();
    void enableCloseEvent(bool enable);
    void connect(uint32_t address);
    void write(uint8_t& data);
    uint64_t write(const uint8_t* slices, uint64_t num_slice);
    void shutdown(int how);
    void onAccept(io_request* req, int32_t result) const;
    void onConnect(io_request* req, int32_t result);
    void onRead(io_request* req, int32_t result);
    void onWrite(io_request* req, int32_t result);
    void onClose(io_request* req, int32_t result);
    void onCancel(io_request* req, int32_t result);
    void onShutdown(io_request* req, int32_t result);
    void setAcceptCallBack(const AcceptCallback& callback);

    IoUringSocketStatus getStatus() const;

private:
    os_fd_t fd{-1};
    IoUringSocketType type{IoUringSocketType::Unknown};
    AcceptCallback acceptCallback = nullptr;
};
}

#endif //IOURINGSOCKET_H
