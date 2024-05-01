//
// Created by Abolfazl Abbasi on 18.04.2024.
//

#ifndef VORTEX_UTILS_H
#define VORTEX_UTILS_H

#include <fcntl.h>
#include "iostream"


namespace vortex::core {

bool makeNonBlocking(const int fd) {
    std::cout << "makeNonBlocking " << fd << std::endl;

    int flags = fcntl(fd, F_GETFL, 0);
    if (flags == -1) {
        std::cerr << "fcntl F_GETFL failed" << std::endl;
        return false;
    }

    flags |= O_NONBLOCK;
    if (fcntl(fd, F_SETFL, flags) == -1) {
        std::cerr << "fcntl F_SETFL failed" << std::endl;
        return false;
    }

    return true;
}
}


#endif //VORTEX_UTILS_H
