cmake_minimum_required(VERSION 3.10)
project(core)

set(BOOST_ROOT "/usr/local/boost_1_76_0")

find_package(Boost 1.76.0 REQUIRED COMPONENTS json)

if (NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found")
endif ()

add_library(core STATIC
        ProcessManager.cpp
        ProcessManager.h
        ServerSocket.cpp
        ServerSocket.h
        worker/WorkerProcess.cpp
        worker/WorkerProcess.h
        config/ConfigLoader.cpp
        config/ConfigLoader.h
        config/Config.cpp
        config/Config.h
)

target_include_directories(core PUBLIC ${Boost_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(core Boost::json)
target_compile_features(core PUBLIC cxx_std_17)
