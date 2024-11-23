cmake_minimum_required(VERSION 3.10)

project(vortex)

set(BOOST_ROOT "/usr/local/boost_1_76_0")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include(FetchContent)
FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 11.0.2
)
FetchContent_MakeAvailable(fmt)

find_package(Boost 1.76.0 REQUIRED COMPONENTS json)

if(NOT Boost_FOUND)
        message(FATAL_ERROR "Boost not found")
endif()

include_directories(/usr/include)
find_library(URING_LIBRARY NAMES uring PATHS /usr/lib/x86_64-linux-gnu/)

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
        core/config/config_loader.cpp
        core/config/config_loader.h
        core/config/config.cpp
        core/config/config.h
        core/config/parser/yaml_parser.cpp
        core/config/parser/yaml_parser.h
)

add_library(vortex STATIC
        common/traits.h

        # Interfaces
        ${VORTEX_INTERFACE_HEADERS}
        # Event module
        ${VORTEX_EVENT_MODULE}
        # config
        ${VORTEX_CONFIG}

        # Core files
        core/process_manager.cpp
        core/process_manager.h
        core/connection_manager.cpp
        core/connection_manager.h
        core/logger/logger.h
        common/address.h
        common/address.cpp
        common/sys_calls_impl.cpp
        common/sys_calls_impl.h

        common/platform.h

        core/io/socket_io_handle_impl.cpp
        core/io/socket_io_handle_impl.h
        core/io/io_uring_dispacher_impl.cpp
        core/io/io_uring_dispacher_impl.h


)


target_include_directories(vortex PUBLIC
        ${Boost_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}
        ${fmt_SOURCE_DIR}/include
)

target_link_libraries(vortex
        Boost::json
        ${URING_LIBRARY}
        fmt
)

target_compile_features(vortex PUBLIC cxx_std_17)

