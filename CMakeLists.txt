# CMakeList.txt : CMake project for ip_filter, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.8)

project(ip_filter)

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else ()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()


add_subdirectory(lib)

add_executable(ip_filter ip_filter.cpp)
target_link_libraries(ip_filter lib)
set_target_properties(ip_filter lib PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        )

# tests
#add_executable(tests tests.cpp)
#find_package(Boost COMPONENTS unit_test_framework REQUIRED)
#set_target_properties(tests PROPERTIES
#        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS}
#        CXX_STANDARD 17
#        CXX_STANDARD_REQUIRED ON
#        )
#target_link_libraries(tests lib ${Boost_LIBRARIES})
#
#enable_testing()
#add_test(ip_filter_tests tests)

