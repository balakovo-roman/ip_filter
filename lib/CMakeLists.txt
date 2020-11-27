cmake_minimum_required(VERSION 3.8)

project(lib)
set(IP_FILTER_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

add_library(lib STATIC ${IP_FILTER_ROOT_DIR}/lib.cpp)
target_include_directories(lib PUBLIC ${IP_FILTER_ROOT_DIR})

