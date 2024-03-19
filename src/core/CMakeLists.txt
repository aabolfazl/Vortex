cmake_minimum_required(VERSION 3.10)

add_library(core STATIC
        ProcessManager.cpp
        ProcessManager.h
        worker/WorkerProcess.cpp
        worker/WorkerProcess.h
)

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
