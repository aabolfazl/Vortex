//
// Created by abolfazl on 10/5/24.
//

#ifndef IOURINGSOCKET_H
#define IOURINGSOCKET_H

#include <IoUring.h>


namespace vortex::event {
class IoUringSocket final {
public:
    ~IoUringSocket() = default;
    IoUringWorker& getIoUringWorker() const;
    os_fd_t fd() const;
    void close(bool keep_fd_open, IoUringSocketOnClosedCb cb = nullptr);
    void enableRead();
    void disableRead();
    void enableCloseEvent(bool enable);
    void connect(uint32_t address);
    void write(uint8_t& data);
    uint64_t write(const uint8_t* slices, uint64_t num_slice);
    void shutdown(int how);
    void onAccept(Request* req, int32_t result, bool injected);
    void onConnect(Request* req, int32_t result, bool injected);
    void onRead(Request* req, int32_t result, bool injected);
    void onWrite(Request* req, int32_t result, bool injected);
    void onClose(Request* req, int32_t result, bool injected);
    void onCancel(Request* req, int32_t result, bool injected);
    void onShutdown(Request* req, int32_t result, bool injected);

    IoUringSocketStatus getStatus() const;
};
}

#endif //IOURINGSOCKET_H