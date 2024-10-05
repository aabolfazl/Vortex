cmake_minimum_required(VERSION 3.10)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(event STATIC
        IoUring.cpp
        IoUring.h
        IoUringWorker.cpp
        IoUringWorker.h
        IoUringSocket.cpp
        IoUringSocket.h
)

include_directories(/usr/include)
find_library(URING_LIBRARY NAMES uring PATHS /usr/lib/x86_64-linux-gnu/)
target_link_libraries(event ${URING_LIBRARY})

target_include_directories(event PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
