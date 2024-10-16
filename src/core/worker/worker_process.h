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

#ifndef WORKERPROCESS_H
#define WORKERPROCESS_H

#include <memory>
#include <sched.h>
#include "tcp_server.h"

namespace vortex::core {
class worker_process {
public:
    explicit worker_process();

    ~worker_process();

    void start() const;

private:
    std::unique_ptr<tcp_server> _server;
    std::unique_ptr<config::ConfigLoader> _config_loader;
};
} // end vortex::core

#endif //WORKERPROCESS_H
