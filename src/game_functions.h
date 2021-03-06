#ifndef GAME_OF_LIFE_GAME_FUNCTIONS_H
#define GAME_OF_LIFE_GAME_FUNCTIONS_H

#include "game_space_structures.h"
#include "game_space_management.h"

unsigned int count_live_neighbors(game_space_t *game_space, unsigned int x, unsigned int y);

bool_t does_cell_die(game_space_t *game_space, unsigned int x, unsigned int y);

bool_t does_cell_revive(game_space_t *game_space, unsigned int x, unsigned int y);

void run_iteration(game_space_t *game_space);

void run_game_of_life__create_a_gif__timebar(game_space_t *game_space, char *name, int iter_per_sec);

void run_game_of_life__create_pngs(game_space_t *game_space, unsigned int snapshot_freq);


#endif //GAME_OF_LIFE_GAME_FUNCTIONS_H
