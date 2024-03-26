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

#ifndef EVENT_H
#define EVENT_H
#include <cstdint>
#include <variant>

#include "../Defines.h"


class Event {
public:
    explicit Event(const EventType type, const int fd)
        : fd(fd), type(type) {
    }

    int fd{-1};
    EventType type;
    uint32_t event{0};
};

#endif //EVENT_H
