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

if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found")
endif ()

include_directories(/usr/include)
find_library(URING_LIBRARY NAMES uring PATHS /usr/lib/x86_64-linux-gnu/)

set(VORTEX_INTERFACE_HEADERS
        core/interfaces/socket_handle.h
        core/interfaces/event/io_uring.h
        core/interfaces/event/io_uring_core.h
        core/interfaces/event/io_uring_socket.h
        core/interfaces/event/io_uring_worker.h
)

add_library(vortex STATIC
        common/traits.h
        ${VORTEX_INTERFACE_HEADERS}

        # Event files
        event/io_uring_core_impl.cpp
        event/io_uring_core_impl.h
        event/io_uring_worker_impl.cpp
        event/io_uring_worker_impl.h
        event/io_uring_socket_impl.cpp
        event/io_uring_socket_impl.h

        # Core files
        core/tcp_server.cpp
        core/tcp_server.h
        core/socket.cpp
        core/socket.h
        core/process_manager.cpp
        core/process_manager.h
        core/worker/worker_process.cpp
        core/worker/worker_process.h
        core/config/ConfigLoader.cpp
        core/config/ConfigLoader.h
        core/config/Config.cpp
        core/config/Config.h
        core/connection_acceptor.cpp
        core/connection_acceptor.h
        core/connection_manager.cpp
        core/connection_manager.h
        core/client/client_connection.cpp
        core/client/client_connection.h
        core/server/server_connection.cpp
        core/server/server_connection.h
        core/logger/logger.h


)

target_include_directories(vortex PUBLIC
        ${Boost_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(vortex
        Boost::json
        ${URING_LIBRARY}
        fmt
)

target_compile_features(vortex PUBLIC cxx_std_17)
