cmake_minimum_required(VERSION 3.16)

project(ipv4)

set(IP_FILTER_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

add_library(ipv4 STATIC ${IP_FILTER_ROOT_DIR}/ipv4.cpp)
target_include_directories(ipv4 PUBLIC ${IP_FILTER_ROOT_DIR})

