cmake_minimum_required(VERSION 3.13)
project(game_of_life C)

set(CMAKE_C_STANDARD 11)

add_executable(
        game_of_life
        src/main.c
        src/game_space_management.c
        src/game_functions.c
        libs/libpng/png.c
        libs/gifdec/gifdec.c
)