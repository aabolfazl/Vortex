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

#include "address.h"

#include <arpa/inet.h>
#include <cstring>

namespace vortex::core {

ipv4::ipv4(const std::string& ip_address, const uint16_t port) : ip_address_(ip_address), port_(port) {

    memset(&addr_, 0, sizeof(addr_));
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port_);
    inet_pton(AF_INET, ip_address_.c_str(), &addr_.sin_addr);
}

auto ipv4::get_sock_addr() const noexcept -> const sockaddr* {
    return reinterpret_cast<const sockaddr*>(&addr_);
}

auto ipv4::sock_addr_len() noexcept -> socklen_t {
    return sizeof(sockaddr_in);
}

auto ipv4::to_string() const noexcept -> std::string {
    return ip_address_;
}

auto ipv4::get_port() const noexcept -> uint16_t {
    return port_;
}

} // namespace vortex::core
