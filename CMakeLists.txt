cmake_minimum_required(VERSION 3.15)
project(pong)

find_package(raylib 3.0 REQUIRED) # Requires at least version 3.0

set(CMAKE_C_STANDARD 11) # Requires C11 standard

add_executable(${PROJECT_NAME} pong.cpp)

target_link_libraries(${PROJECT_NAME} raylib)
