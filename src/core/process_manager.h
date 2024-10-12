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

#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <mutex>
#include <vector>
#include <sys/types.h>

namespace vortex::core {
class process_manager {
public:
    process_manager() = default;

    static u_int get_cores_size();

    void create_workers();

private:
    std::vector<pid_t> workerProcesses = {};
};
}

#endif //PROCESSMANAGER_H
