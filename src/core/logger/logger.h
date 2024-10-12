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

#ifndef LOGGER_H
#define LOGGER_H
#pragma once

#include <fmt/format.h>
#include <fmt/chrono.h>
#include <chrono>

namespace vortex::core {
class logger {
public:
    enum class log_level { info, error };

    template <typename... Args>
    static void info(const char* format, Args&&... args) {
        log(log_level::info, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void error(const char* format, Args&&... args) {
        log(log_level::error, format, std::forward<Args>(args)...);
    }

private:

    template <typename... Args>
    static void log(const log_level level, const char* format, Args&&... args) {
        const auto now = std::chrono::system_clock::now();
        const auto time = std::chrono::system_clock::to_time_t(now);

        fmt::memory_buffer buffer;
        fmt::format_to(std::back_inserter(buffer), "{:%Y-%m-%d %H:%M:%S} {} ", *std::localtime(&time), log_level_to_string(level));

        fmt::format_to(std::back_inserter(buffer), format, std::forward<Args>(args)...);
        fmt::format_to(std::back_inserter(buffer), "\n");

        fmt::print("{}", fmt::to_string(buffer));
    }

    static const char* log_level_to_string(const log_level level) {
        switch (level){
        case log_level::info: return "I";
        case log_level::error: return "D";
        default: return "UNKNOWN";
        }
    }
};
}
#endif //LOGGER_H
