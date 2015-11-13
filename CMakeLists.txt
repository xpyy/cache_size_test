cmake_minimum_required(VERSION 3.3)
project(cache_size_test)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")

set(SOURCE_FILES main.c)
add_definitions(-std=gnu99)
add_executable(cache_size_test ${SOURCE_FILES})