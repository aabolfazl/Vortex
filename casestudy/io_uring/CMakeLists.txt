cmake_minimum_required(VERSION 3.20)
project(IO_URING)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(IO_URING io_uring.cpp)

include_directories(/usr/include)
target_link_libraries(io_uring /usr/lib/aarch64-linux-gnu/liburing.so)