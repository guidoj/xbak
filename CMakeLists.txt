cmake_minimum_required(VERSION 3.20)

# set the project name
project(xBaK)

find_package(SDL2 REQUIRED)
find_package(SDL2_mixer REQUIRED)

add_compile_options(-ansi -pedantic -std=c++11 -Wall -Wextra -Wpointer-arith -Wcast-qual -Wwrite-strings -Wshadow -Wcast-align -Werror)
add_link_options(-Wl,--as-needed)
include_directories(${SDL2_INCLUDE_DIRS})

add_subdirectory(src)
