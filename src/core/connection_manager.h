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

#include <memory>
#include <unordered_map>

namespace vortex::core {
class connection_manager final {
public:
    explicit connection_manager();
    ~connection_manager();

    void start_accept_connections();

private:
    void on_new_connection_established(int fd);
    auto init_servers_list() -> void;
};

using connection_manager_ptr = std::shared_ptr<connection_manager>;

} // namespace vortex::core