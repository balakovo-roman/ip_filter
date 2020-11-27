# CMakeList.txt : CMake project for ip_filter, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project (ip_filter)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_subdirectory(lib)

# Add source to this project's executable.
add_executable (ip_filter "ip_filter.cpp")
target_link_libraries(ip_filter lib)

# TODO: Add tests and install targets if needed.
add_executable(tests "tests.cpp")
target_include_directories(tests PUBLIC ${Boost_INCLUDE_DIR})
target_link_libraries(tests lib ${Boost_LIBRARIES})

set_target_properties(ip_filter lib tests PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
#        CXX_EXTENSIONS OFF
        )

if (MSVC)
    # warning level 4 and all warnings as errors
    add_compile_options(/W4 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

install(TARGETS ip_filter
        CONFIGURATIONS Release
        RUNTIME DESTINATION bin)
