cmake_minimum_required(VERSION 3.20)
project(Vortex)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src/core)
add_subdirectory(src/event)

add_executable(Vortex main.cpp
        src/VortexApp.cpp
        src/VortexApp.h)

target_link_libraries(${PROJECT_NAME} core event)