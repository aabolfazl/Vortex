cmake_minimum_required(VERSION 3.10)
project(core)

set(BOOST_ROOT "/usr/local/boost_1_76_0")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(Boost 1.76.0 REQUIRED COMPONENTS json)

if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found")
endif ()

add_library(core STATIC
        process_manager.cpp
        process_manager.h
        worker/worker_process.cpp
        worker/worker_process.h
        config/ConfigLoader.cpp
        config/ConfigLoader.h
        config/Config.cpp
        config/Config.h
        ../Vortex.h
        utils.h
        tcp_server.cpp
        tcp_server.h
        socket.cpp
        socket.h
        connection_acceptor.cpp
        connection_acceptor.h
        connection_manager.cpp
        connection_manager.h
        logger/logger.h
)

target_include_directories(core PUBLIC ${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR} ./../event/)

target_link_libraries(core Boost::json fmt)
target_compile_features(core PUBLIC cxx_std_17)
