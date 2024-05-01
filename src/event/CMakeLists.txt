cmake_minimum_required(VERSION 3.10)

add_library(event STATIC
        EventDefines.h
        EventLoop.cpp
        EventLoop.h
        EventHandler.cpp
        EventHandler.h
)

include_directories(/usr/include)
target_link_libraries(event /usr/lib/aarch64-linux-gnu/liburing.so)

target_include_directories(event PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
