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

#ifndef VORTEX_EVENT_HANDLER_H
#define VORTEX_EVENT_HANDLER_H

#include <functional>
#include "string"
#include "../Vortex.h"
#include "EventDefines.h"
#include <any>

namespace vortex::event {

using EventCallback = std::function<bool(const std::any &)>;

class EventInterface {
public:
    virtual ~EventInterface() = default;

    virtual auto onEvent(const std::any &event) -> bool = 0;
};

class EventHandler final : EventInterface {
public:
    explicit EventHandler(int type, int fd);

    ~EventHandler();

    bool onEvent(const std::any &event) override;

    auto setEventCallback(const EventCallback &callback) -> void;

    int getType() const {
        return type;
    };

    int getFd() const {
        return fd;
    };

private:
    int type;
    int fd;
    uint8_t flags{};
    EventCallback eventCallback{};
};

}

#endif //VORTEX_EVENT_HANDLER_H
