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

#include "WorkerProcess.h"

#include <iostream>

namespace vortex::core {
WorkerProcess::WorkerProcess(
    const pid_t pid,
    const std::string &configPath
): pid(pid),
   configLoader(std::make_unique<config::ConfigLoader>(configPath)),
   epoll(std::make_unique<event::EPoll>()) {
    const auto config = configLoader->load();
    const auto [readBuffer, writeBuffer] = config->buffers;
    const auto port = config->listener.port;

    socket = std::make_unique<ServerSocket>(readBuffer, writeBuffer, port);

    socket->onClientAccepted = [this](const int fd) {
        this->onNewClientConected(fd);
    };

    epoll->eventHandler = [this](const epoll_event event) {
        this->onNewEvent(event);
    };
}

auto WorkerProcess::onNewEvent(const epoll_event epollEvent) const -> void {
    std::cout << "onNewEvent: " << epollEvent.events << std::endl;

    const auto event = static_cast<Event *>(epollEvent.data.ptr);

    switch (event->type) {
        case ListenrSocket: {
            socket->handleEvent(event, epollEvent.events);
            break;
        }
        default:
            break;
    }
}

void WorkerProcess::start() const {
    try {
        const auto socketFd = socket->startListening();
        const auto event = new Event(ListenrSocket, socketFd);
        epoll->addListenerSocket(event);
    } catch (const std::exception &e) {
        std::cerr << "Failed to startListening: " << e.what() << std::endl;
    }

    epoll->wait();

    _exit(0);
}

auto WorkerProcess::onNewClientConected(const int fd) -> void {
    std::cerr << "onNewClientConected " << fd << std::endl;
}

WorkerProcess::~WorkerProcess() = default;
}
