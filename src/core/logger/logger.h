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

#include <chrono>
#include <fmt/chrono.h>
#include <fmt/format.h>
#include <iostream>
#include <unistd.h>

constexpr std::string_view extract_filename(std::string_view path) {
    size_t pos = path.find_last_of("/\\");
    return (pos == std::string_view::npos) ? path : path.substr(pos + 1);
}

#define LOG_I(fmt, ...) vortex::core::logger::info(extract_filename(__FILE__).data(), fmt, ##__VA_ARGS__)
#define LOG_E(fmt, ...) vortex::core::logger::error(extract_filename(__FILE__).data(), fmt, ##__VA_ARGS__)
#define LOG_W(fmt, ...) vortex::core::logger::warn(extract_filename(__FILE__).data(), fmt, ##__VA_ARGS__)
#define LOG_D(fmt, ...) vortex::core::logger::debug(extract_filename(__FILE__).data(), fmt, ##__VA_ARGS__)

namespace vortex::core {
class logger {
public:
    enum class log_level { info, error, warning, debug };

    template <typename... Args>
    static void info(const char* format, Args&&... args) {
        log(log_level::info,nullptr, format, std::forward<Args>(args)...);
    }
    template <typename... Args>
    static void info(const char* filename, const char* format, Args&&... args) {
        log(log_level::info, filename, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void error(const char* format, Args&&... args) {
        log(log_level::error, nullptr, format, std::forward<Args>(args)...);
    }
    template <typename... Args>
    static void error(const char* filename, const char* format, Args&&... args) {
        log(log_level::error, filename, format, std::forward<Args>(args)...);
    }

    template <typename... Args>
    static void warn(const char* format, Args&&... args) {
        log(log_level::warning, nullptr, format, std::forward<Args>(args)...);
    }
    template <typename... Args>
    static void warn(const char* filename, const char* format, Args&&... args) {
        log(log_level::warning, filename, format, std::forward<Args>(args)...);
    }


    template <typename... Args>
    static void debug(const char* format, Args&&... args) {
        log(log_level::debug, format, std::forward<Args>(args)...);
    }
    template <typename... Args>
    static void debug(const char* filename, const char* format, Args&&... args) {
        log(log_level::debug, filename, format, std::forward<Args>(args)...);
    }

private:
    template <typename... Args>
    static void log(const log_level level, const char* filename, const char* format, Args&&... args) {
        const auto now = std::chrono::system_clock::now();
        const auto time = std::chrono::system_clock::to_time_t(now);


        fmt::memory_buffer buffer;

        if (filename) {
            fmt::format_to(std::back_inserter(buffer), "{:%Y-%m-%d %H:%M:%S} {} {} {} : ", *std::localtime(&time),
                           getpid(), log_level_to_string(level), filename);
        } else {
            fmt::format_to(std::back_inserter(buffer), "{:%Y-%m-%d %H:%M:%S} {} {} : ", *std::localtime(&time),
                           getpid(), log_level_to_string(level));
        }

        fmt::format_to(std::back_inserter(buffer), format, std::forward<Args>(args)...);
        fmt::format_to(std::back_inserter(buffer), "\n");

        std::string color_code;
        switch (level) {
        case log_level::error:
            color_code = "\033[31m";
            break;
        case log_level::warning:
            color_code = "\033[33;1m";
            break;
        case log_level::debug:
            color_code = "\033[36m";
            break;
        default:
            color_code = "\033[0m";
            break;
        }

        fmt::print("{}{}{}", color_code, fmt::to_string(buffer), "\033[0m");
    }

    static const char* log_level_to_string(const log_level level) {
        switch (level) {
        case log_level::info:
            return "I";
        case log_level::error:
            return "E";
        case log_level::warning:
            return "W";
        case log_level::debug:
            return "D";
        default:
            return "UNKNOWN";
        }
    }
};
} // namespace vortex::core
