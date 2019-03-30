cmake_minimum_required(VERSION 3.13)
project(game_of_life C)

set(CMAKE_C_STANDARD 11)

add_executable(
        game_of_life
        src/main.c
        src/game_space_management.c src/game_space_management.h
        src/game_functions.c src/game_functions.h
        src/game_space_display.c src/game_space_display.h
        libs/gifenc/gifenc.c libs/gifenc/gifenc.h
        libs/lodepng/lodepng.c libs/lodepng/lodepng.h
        src/game_configuration.c src/game_configuration.h
)