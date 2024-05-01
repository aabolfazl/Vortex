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

#ifndef VORTEX_EVENTLOOP_H
#define VORTEX_EVENTLOOP_H

#include "EventDefines.h"
#include "EventHandler.h"

#include <iostream>
#include <vector>
#include <functional>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <liburing.h>

namespace vortex::event {

class EventLoop {
public:
    explicit EventLoop();

    ~EventLoop();

    EventLoop(EventLoop &&) noexcept(true) = default;

    EventLoop &operator=(EventLoop &&) noexcept(true) = default;

    auto add(EventHandler *handler) -> bool;

    auto remove(EventHandler *handler) const -> void;

    [[noreturn]] auto loop() -> void;

private:
    io_uring ring{};
};
}

#endif //VORTEX_EVENTLOOP_H
