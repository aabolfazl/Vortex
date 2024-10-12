//
// Created by Abolfazl Abbasi on 18.04.2024.
//

#ifndef VORTEX_UTILS_H
#define VORTEX_UTILS_H

#include <fcntl.h>
#include "iostream"
#include "logger/logger.h"


namespace vortex::core {
inline bool make_non_blocking(const int fd) {
    logger::info("makeNonBlocking {}", fd);

    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1){
        logger::error("fcntl F_GETFL failed");
        return false;
    }

    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) == -1){
        logger::error("fcntl F_SETFL failed");
        return false;
    }

    return true;
}
}


#endif //VORTEX_UTILS_H
