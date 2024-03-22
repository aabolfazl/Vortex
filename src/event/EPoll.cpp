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

void EPoll::setEventHandler(const EventHandler&handler) {
    this->eventHandler = handler;
}

void EPoll::add(const int fd) const {
    epoll_event event{
        .events = EPOLLIN,
        .data = {.fd = fd}
    };

    if (epoll_ctl(epollFd, EPOLL_CTL_ADD, fd, &event) < 0) {
        throw std::runtime_error("Failed to add file descriptor to epoll");
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
        const int nEvents = epoll_wait(epollFd, events.data(), MAX_EVENTS, -1);
        if (nEvents == -1) {
            throw std::runtime_error("Epoll wait error");
        }
        for (int i = 0; i < nEvents; ++i) {
            const int fd = events[i].data.fd;
            const uint32_t eventTypes = events[i].events;
            eventHandler(fd, eventTypes);
        }
    }
}

EPoll::~EPoll() {
    if (epollFd != -1) {
        close(epollFd);
    }
}
} // end vortex::event
