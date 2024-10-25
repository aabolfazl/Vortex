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

#pragma once

namespace vortex::traits {

template <typename T>
class non_copyable {
protected:
    non_copyable() = default;
    ~non_copyable() = default;

public:
    non_copyable(const non_copyable &) = delete;
    non_copyable &operator=(const non_copyable &) = delete;
};

template <typename T>
class non_moveable {
protected:
    non_moveable() = default;
    ~non_moveable() = default;

public:
    non_moveable(non_moveable &&) = delete;
    non_moveable &operator=(non_moveable &&) = delete;
};

} // namespace vortex::traits
