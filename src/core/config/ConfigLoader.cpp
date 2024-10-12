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

#include "ConfigLoader.h"

#include <fstream>
#include <iostream>
#include <boost/json/parse.hpp>
#include <utility>

namespace vortex::core::config {
ConfigLoader::ConfigLoader(
    std::string configFile
) : filePath(std::move(configFile)) {
    load();
}

void ConfigLoader::readFile() {
    if (std::ifstream ifs(filePath); ifs) {
        try {
            const std::string jsonContent(
                (std::istreambuf_iterator(ifs)),
                (std::istreambuf_iterator<char>())
            );

            config = boost::json::parse(jsonContent).as_object();
        } catch (const std::exception &e) {
            std::cerr << "Failed to parse config: " << e.what() << std::endl;
        }

        ifs.close();
    } else {
        throw std::runtime_error("Unable to open config file: " + filePath);
    }
}

auto ConfigLoader::load() -> std::shared_ptr<Config> {
    if (config.empty()) {
        readFile();
    }

    return Config::fromJson(config);
}
}
