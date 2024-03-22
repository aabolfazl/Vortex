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

#ifndef EPOLL_H
#define EPOLL_H
#include <cstdint>
#include <functional>

namespace vortex::event {
constexpr int MAX_EVENTS = 10;

class EPoll {
public:
    using EventHandler = std::function<void(int fd, uint32_t events)>;

    EPoll();
    ~EPoll();

    void add(int fd) const;
    void remove(int fd) const;
    void wait() const;
    void setEventHandler(const EventHandler&handler);

private:
    int epollFd = {-1};
    EventHandler eventHandler;
};
}


#endif //EPOLL_H
