cmake_minimum_required(VERSION 3.10)

add_library(event STATIC
        EPoll.h
        EPoll.cpp
        Event.cpp
        Event.h
)

target_include_directories(event PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
