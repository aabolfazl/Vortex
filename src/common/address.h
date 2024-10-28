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

#include <arpa/inet.h>
#include <cstring>
#include <netinet/in.h>
#include <string>

namespace vortex::core {
class ipv4 {
public:
    explicit ipv4(const std::string &ip_address, uint16_t port = 8080);

    auto get_sock_addr() const -> const sockaddr *;
    static auto sock_addr_len() -> socklen_t;
    auto to_string() const -> std::string;

    auto get_port() const -> uint16_t;

private:
    sockaddr_in addr_{};
    std::string ip_address_;
    uint16_t port_;
};
} // namespace vortex::core
