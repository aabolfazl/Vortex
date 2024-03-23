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

#include "src/VortexApp.h"

int main() {
    const auto server = new vortex::VortexApp("/config.json");
    server->start();

    return 0;
}
