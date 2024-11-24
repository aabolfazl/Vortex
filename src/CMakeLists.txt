cmake_minimum_required(VERSION 3.10)
project(vortex VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 11.0.2
)

FetchContent_Declare(
        yaml-cpp
        GIT_REPOSITORY https://github.com/jbeder/yaml-cpp.git
        GIT_TAG yaml-cpp-0.7.0 # Using a known good version
)

set(YAML_CPP_BUILD_TESTS OFF CACHE BOOL "disable yaml-cpp tests")
set(YAML_CPP_BUILD_TOOLS OFF CACHE BOOL "disable yaml-cpp tools")
set(YAML_CPP_BUILD_CONTRIB OFF CACHE BOOL "disable yaml-cpp contrib")
set(YAML_CPP_INSTALL OFF CACHE BOOL "disable yaml-cpp install")

FetchContent_MakeAvailable(fmt yaml-cpp)

find_package(PkgConfig REQUIRED)
pkg_check_modules(URING REQUIRED liburing)

set(VORTEX_INTERFACE_HEADERS
        core/interfaces/event/io_uring.h
        core/interfaces/event/io_uring_core.h
        core/interfaces/sys_calls.h
        core/interfaces/io_handle.h
        core/interfaces/event/async_event.h
        core/interfaces/event/dispatcher.h
)

set(VORTEX_EVENT_MODULE
        event/io_uring_core_impl.cpp
        event/io_uring_core_impl.h
)

set(VORTEX_CONFIG
        core/config/types.h
        core/config/config_manager.cpp
        core/config/config_manager.h
        core/config/parser_interface.h
        core/config/yaml_parser.cpp
        core/config/yaml_parser.h
)

set(VORTEX_COMMON
        common/traits.h
        common/address.h
        common/address.cpp
        common/sys_calls_impl.cpp
        common/sys_calls_impl.h
        common/platform.h
)



set(VORTEX_LISTENER
        core/listener/listener_manager.h
)

set(VORTEX_CORE
        core/service_node.h
        core/service_node.cpp
        
        core/logger/logger.h
        core/io/socket_io_handle_impl.cpp
        core/io/socket_io_handle_impl.h
        core/io/io_uring_dispacher_impl.cpp
        core/io/io_uring_dispacher_impl.h
)

add_library(vortex STATIC
        ${VORTEX_INTERFACE_HEADERS}
        ${VORTEX_EVENT_MODULE}
        ${VORTEX_CONFIG}
        ${VORTEX_COMMON}
        ${VORTEX_CORE}
        ${VORTEX_LISTENER}
)

target_include_directories(vortex
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
        PRIVATE
        ${URING_INCLUDE_DIRS}
)

target_link_libraries(vortex
        PUBLIC
        fmt::fmt
        yaml-cpp
        PRIVATE
        ${URING_LIBRARIES}
)
