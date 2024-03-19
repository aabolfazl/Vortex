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
#include <sched.h>

namespace vortex::core {
class WorkerProcess {
public:
    explicit WorkerProcess(pid_t pid_);
    ~WorkerProcess();

    void start() const;

private:
    pid_t pid = {};
};
}


#endif //WORKERPROCESS_H
