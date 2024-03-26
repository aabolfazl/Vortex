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
#include <sys/epoll.h>

#include "EventListener.h"

namespace vortex::event {
constexpr int MAX_EVENTS = 10;

class EPoll {
public:
    EPoll();
    ~EPoll();

    auto addListenerSocket(Event* event) const -> void;
    auto remove(int fd) const -> void;
    auto wait() const -> void;

    std::function<void(epoll_event event)> eventHandler;

private:
    int epollFd = {-1};
};
}


#endif //EPOLL_H
