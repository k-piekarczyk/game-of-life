//
// Created by Krzysztof Piekarczyk on 2019-03-21.
//

#ifndef GAME_OF_LIFE_GAME_FUNCTIONS_H
#define GAME_OF_LIFE_GAME_FUNCTIONS_H

#include "game_space_structures.h"
#include "game_space_management.h"

unsigned int count_live_neighbours(game_space_t *game_space, unsigned int x, unsigned int y);

bool_t does_cell_die(game_space_t *game_space, unsigned int x, unsigned int y);

bool_t does_cell_revive(game_space_t *game_space, unsigned int x, unsigned int y);

void run_iteration(game_space_t *game_space);

void print_game_state(game_space_t *game_space);

void run_game_of_life(game_space_t *game_space, unsigned int snapshot_freq);

#endif //GAME_OF_LIFE_GAME_FUNCTIONS_H
