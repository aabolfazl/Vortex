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

#include "EPoll.h"

#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/epoll.h>

namespace vortex::event {
EPoll::EPoll() {
    epollFd = epoll_create1(0);
    if (epollFd == -1) {
        throw std::runtime_error("Failed to create epoll file descriptor");
    }
}

void EPoll::addListenerSocket(Event* event) const {
    constexpr uint32_t events = EPOLLOUT | EPOLLIN | EPOLLRDHUP | EPOLLERR | EPOLLET;

    epoll_event epoll_event{};
    epoll_event.events = events;
    epoll_event.data = {};
    epoll_event.data.ptr = event;

    std::cout << "addListenerSocket: " << event->type << std::endl;

    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, event->fd, &epoll_event) < 0) {
        throw std::runtime_error("Failed to add ListenerSocket to epoll");
    }
}

void EPoll::remove(const int fd) const {
    if (epoll_ctl(epollFd, EPOLL_CTL_DEL, fd, nullptr) < 0) {
        throw std::runtime_error("Failed to add file descriptor to epoll");
    }
}

void EPoll::wait() const {
    if (!eventHandler) {
        throw std::runtime_error("Event handler not set");
    }

    while (true) {
        std::vector<epoll_event> events(MAX_EVENTS);
        const int eventsCount = epoll_wait(epollFd, events.data(), MAX_EVENTS, -1);

        if (eventsCount == -1) {
            std::cerr << "Epoll wait error" << std::endl;
            continue;
        }

        for (int i = 0; i < eventsCount; i++) {
            eventHandler(events[i]);
        }
    }
}

EPoll::~EPoll() {
    if (epollFd != -1) {
        close(epollFd);
    }
}
} // end vortex::event
