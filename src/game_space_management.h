#ifndef GAME_OF_LIFE_GAME_SPACE_H
#define GAME_OF_LIFE_GAME_SPACE_H

#include <stdlib.h>
#include <time.h>

#include "game_space_structures.h"


game_space_t *create_blank_game_space(unsigned int x_dim, unsigned int y_dim);

void set_max_iterations(game_space_t *game_space, unsigned int iter);

void randomise_game_space(game_space_t *game_space);

void plane_dimension_guard(game_space_t *game_space, unsigned int x, unsigned int y);

void flip_cell_state(game_space_t *game_space, unsigned int x, unsigned int y);

unsigned char check_cell_state(game_space_t *game_space, unsigned int x, unsigned int y);

game_space_t *copy_game_space(game_space_t *game_space);

void free_game_space(game_space_t *game_space);


#endif //GAME_OF_LIFE_GAME_SPACE_H
