cmake_minimum_required(VERSION 3.16)

project(ipv4_tests)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

add_executable(ipv4_tests main_tests.cpp)
target_include_directories(ipv4_tests PRIVATE ${CMAKE_SOURCE_DIR}/ipv4 ${GTEST_INCLUDE_DIRS})
target_link_libraries(ipv4_tests PRIVATE ipv4 gtest gtest_main Threads::Threads)
set_target_properties(
        ipv4_tests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
