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

#include "src/vortex_app.h"
#include <iostream>
#include <fstream>

int main(const int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <config-file-path>" << std::endl;
        return 1;
    }

    const std::string configFilePath = argv[1];

    if (!std::ifstream(configFilePath)) {
        std::cerr << "Config file not found: " << configFilePath << std::endl;
        return 1;
    }

    auto server = vortex::vortex_app(configFilePath);
    server.start();

    return 0;
}
