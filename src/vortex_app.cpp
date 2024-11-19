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

#include "vortex_app.h"
#include "core/io/io_uring_dispacher_impl.h"
#include "core/io/socket_io_handle_impl.h"
#include "core/logger/logger.h"

#include <stdlib.h>
#include <string>
#include <thread>

namespace vortex {
vortex_app::vortex_app(const std::string &configFile) {
    setenv("config_file", configFile.data(), 1);
}

void vortex_app::start() {
    // processManager = std::make_unique<core::process_manager>();
    // processManager->create_workers();

    core::logger::info("Starting Vortex application");

    auto dispatcher = std::make_unique<vortex::event::io_uring_dispacher_impl>();
    auto socket = vortex::core::socket_io_handle_impl::create_tcp();

    if (socket == nullptr) {
        return;
    }

    core::logger::info("Socket created successfully {}", socket->fd());
    socket->set_blocking(false);
    const int opt = 1;
    socket->set_socket_option(SOL_SOCKET, SO_REUSEPORT, &opt, sizeof opt);

    core::logger::info("Binding to aaa port 8080");

    socket->bind(8585);
    socket->listen();

    auto accept_operation = std::make_unique<vortex::event::accept_operation>(socket->fd(), [&](int result) {
         core::logger::info("Accept operation completed with result {}", result); 
    });

    dispatcher->submit_async_accept(std::move(accept_operation));

    dispatcher->loop();
}
} // namespace vortex
