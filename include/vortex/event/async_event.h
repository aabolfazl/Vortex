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

#include <cstdint>
#include <functional>
#include <memory>
#include "common/address.h"
#include "common/platform.h"


namespace vortex::event {

using file_ready_cb = std::function<void(int32_t fd, uint32_t events)>;

enum class operation_type {
    read,
    write,
    error,
    close,
    accept,
    connect,
};

class io_operation {
public:
    virtual ~io_operation() = default;
    virtual void complete(int result) = 0;
    virtual operation_type type() const = 0;


    std::string type_str() const {
        switch (type()) {
        case operation_type::read:
            return "read";
        case operation_type::write:
            return "write";
        case operation_type::error:
            return "error";
        case operation_type::close:
            return "close";
        case operation_type::accept:
            return "accept";
        case operation_type::connect:
            return "connect";
        }
        return "unknown";
    }
};

class accept_operation : public io_operation {
public:
    std::function<void(int)> callback;
    os_fd_t fd = 0;

    explicit accept_operation(os_fd_t fd, std::function<void(int)> cb) : fd(fd), callback(std::move(cb)) {
    }

    void complete(int result) override {
        callback(result);
    }

    operation_type type() const override {
        return operation_type::accept;
    }
};
using accept_operation_ptr = std::unique_ptr<accept_operation>;

class connect_operation : public io_operation {
public:
    std::function<void(int)> callback_;
    os_fd_t fd_ = 0;
    core::ipv4_ptr address_;

    explicit connect_operation(os_fd_t fd, core::ipv4_ptr address, std::function<void(int)> cb) :
        fd_(fd), callback_(std::move(cb)), address_(address) {
    }

    void complete(int result) override {
        callback_(result);
    }

    operation_type type() const override {
        return operation_type::connect;
    }
};
using connect_operation_ptr = std::unique_ptr<connect_operation>;

} // namespace vortex::event
