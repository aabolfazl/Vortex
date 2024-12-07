cmake_minimum_required(VERSION 3.20)
project(vortex_tests)

include(FetchContent)
fetchcontent_declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)
fetchcontent_makeavailable(googletest)

enable_testing()

add_executable(vortex_tests
    listener/listener_test.cpp
)

target_link_libraries(vortex_tests
    PRIVATE
    GTest::gtest_main
    GTest::gmock_main
    vortex
    ${URING_LIBRARY}
    fmt
)

target_include_directories(vortex_tests
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

include(GoogleTest)
gtest_discover_tests(vortex_tests)

set_target_properties(vortex_tests
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
