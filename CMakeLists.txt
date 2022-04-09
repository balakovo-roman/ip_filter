# CMakeList.txt : CMake project for ip_filter, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.16)

project(ip_filter)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else ()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif ()

add_subdirectory(ipv4)
add_subdirectory(tests)

add_executable(ip_filter ip_filter.cpp)
target_include_directories(ip_filter PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/ipv4)
target_link_libraries(ip_filter ipv4)
set_target_properties(
        ip_filter ipv4 PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
)
