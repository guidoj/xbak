cmake_minimum_required(VERSION 3.20)

# set the project name
project(xBaK)

find_package(SDL REQUIRED)
find_package(SDL_mixer REQUIRED)
find_package(SDL_sound REQUIRED)

add_compile_options(-ansi -pedantic -Wall -Wextra -Wpointer-arith -Wcast-qual -Wwrite-strings -Wshadow -Wcast-align -Werror)
add_link_options(-Wl,--as-needed)
include_directories(${SDL_INCLUDE_DIRS})

add_subdirectory(src)

