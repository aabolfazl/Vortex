cmake_minimum_required(VERSION 3.20)
project(Vortex VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

fetchcontent_declare(
    fmt
    GIT_REPOSITORY https://github.com/fmtlib/fmt.git
    GIT_TAG 11.0.2
)

fetchcontent_declare(
    yaml-cpp
    GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
    GIT_TAG yaml-cpp-0.7.0
)

set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "disable yaml-cpp tests")
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "disable yaml-cpp tools")
set(YAML_CPP_BUILD_CONTRIB OFF CACHE BOOL "disable yaml-cpp contrib")
set(YAML_CPP_INSTALL OFF CACHE BOOL "disable yaml-cpp install")

fetchcontent_makeavailable(fmt yaml-cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(URING REQUIRED liburing)

include(CTest)
enable_testing()

add_subdirectory(src)
add_subdirectory(test/cpp)

add_executable(${PROJECT_NAME} 
    main.cpp
    src/vortex_app.cpp
    src/vortex_app.h
)

target_include_directories(${PROJECT_NAME} 
    PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(${PROJECT_NAME} vortex)

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
    ${CMAKE_BINARY_DIR}/compile_commands.json
    ${CMAKE_SOURCE_DIR}/compile_commands.json
)