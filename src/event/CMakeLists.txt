cmake_minimum_required(VERSION 3.10)

add_library(event STATIC
        io_uring_core.cpp
        io_uring_core.h
        IoUringWorker.cpp
        IoUringWorker.h
        io_uring_socket.cpp
        io_uring_socket.h
)

include_directories(/usr/include)
find_library(URING_LIBRARY NAMES uring PATHS /usr/lib/x86_64-linux-gnu/)
target_link_libraries(event ${URING_LIBRARY})

target_include_directories(event PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
