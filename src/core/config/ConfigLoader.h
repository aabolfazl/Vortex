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


#ifndef CONFIGLOADER_H
#define CONFIGLOADER_H

#include <boost/json/object.hpp>
#include <memory>
#include <string>
#include "Config.h"

namespace vortex::core::config {
class ConfigLoader final {
public:
    explicit ConfigLoader(std::string configFile);

    void load();

private:
    std::string filePath;
    boost::json::object config;
    void readFile();
};
} // namespace vortex::core::config
#endif // CONFIGLOADER_H
