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
#include <memory>
#include <string>
#include <boost/json/object.hpp>
#include "Config.h"

namespace vortex::core::config {
class ConfigLoader {
public:
    explicit ConfigLoader(std::string configFile);

    auto load() -> std::shared_ptr<Config>;

private:
    std::string filePath;
    boost::json::object config;
    void readFile();
};
}
#endif //CONFIGLOADER_H
