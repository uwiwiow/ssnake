cmake_minimum_required(VERSION 3.28)
project(Snake C)

set(CMAKE_C_STANDARD 23)

find_package(raylib REQUIRED)
add_executable(Snake src/main.c
        include/cvector.h)

target_link_libraries(Snake raylib GL m pthread dl rt X11)
target_include_directories(Snake PRIVATE include)