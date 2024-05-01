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

#include "EventHandler.h"

namespace vortex::event {

EventHandler::EventHandler(int type, int fd) : type(type), fd(fd) {

}

bool EventHandler::onEvent(const std::any &event) {
    if (eventCallback) {
        return eventCallback(event);
    }
    return false;
}

auto EventHandler::setEventCallback(const EventCallback &callback) -> void {
    EventHandler::eventCallback = callback;
}

EventHandler::~EventHandler() {

}

}