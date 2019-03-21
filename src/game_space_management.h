//
// Created by Krzysztof Piekarczyk on 2019-02-21.
//

#ifndef GAME_OF_LIFE_GAME_SPACE_H
#define GAME_OF_LIFE_GAME_SPACE_H

#include <stdlib.h>
#include <time.h>

#include "game_space_structures.h"


game_space_t *create_blank_game_space(unsigned int x_dim, unsigned int y_dim, unsigned int iterations);

void randomise_game_space(game_space_t *game_space);

void __plane_dimension_guard(game_space_t *game_space, unsigned int x, unsigned int y);

void change_cell_state(game_space_t *game_space, unsigned int x, unsigned int y);

unsigned char check_cell_state(game_space_t *game_space, unsigned int x, unsigned int y);

game_space_t *copy_game_space(game_space_t *game_space);

void free_game_space(game_space_t *game_space);

#endif //GAME_OF_LIFE_GAME_SPACE_H
