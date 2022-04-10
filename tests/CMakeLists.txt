cmake_minimum_required(VERSION 3.16)

project(ipv4_tests)

find_package(GTest REQUIRED)
find_package(Threads REQUIRED)

enable_testing()

add_executable(ipv4_tests main_tests.cpp)

add_custom_command(
        TARGET ipv4_tests
        POST_BUILD
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/ip_filter.tst ${CMAKE_CURRENT_BINARY_DIR}/ip_filter.tst
        COMMAND cp ${CMAKE_CURRENT_SOURCE_DIR}/ip_filter.tsv ${CMAKE_CURRENT_BINARY_DIR}/ip_filter.tsv
)

target_include_directories(ipv4_tests PRIVATE ${CMAKE_SOURCE_DIR}/ipv4 ${GTEST_INCLUDE_DIRS})
target_link_libraries(ipv4_tests PRIVATE ipv4 gtest gtest_main Threads::Threads)
set_target_properties(
        ipv4_tests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)

gtest_discover_tests(ipv4_tests)
