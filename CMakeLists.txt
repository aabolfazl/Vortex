cmake_minimum_required(VERSION 3.20)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(Vortex)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
# add_subdirectory(test/cpp)

add_executable(Vortex main.cpp
        src/vortex_app.cpp
        src/vortex_app.h
)

target_link_libraries(${PROJECT_NAME} vortex)

add_custom_command(TARGET Vortex POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_BINARY_DIR}/compile_commands.json
        ${CMAKE_SOURCE_DIR}/compile_commands.json
)
