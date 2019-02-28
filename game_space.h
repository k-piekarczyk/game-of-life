//
// Created by Krzysztof Piekarczyk on 2019-02-21.
//

#ifndef GAME_OF_LIFE_GAME_SPACE_H
#define GAME_OF_LIFE_GAME_SPACE_H

#include <stdlib.h>
#include <time.h>

enum cell_state {DEAD=45, ALIVE=35};
typedef enum bool_e {FALSE, TRUE} bool_t;

typedef struct game_space_s {
    unsigned int x_dim;
    unsigned int y_dim;
    unsigned int current_iteration;
    unsigned int max_iterations;
    unsigned char **plane;
} game_space_t;

game_space_t *create_blank_game_space(unsigned int x_dim, unsigned int y_dim, unsigned int iterations);

void randomise_game_space(game_space_t *game_space);

void __plane_dimension_guard(game_space_t *game_space, unsigned int x, unsigned int y);

unsigned int count_live_neighbours(game_space_t *game_space, unsigned int x, unsigned int y);

bool_t does_cell_die(game_space_t *game_space, unsigned int x, unsigned int y);

bool_t does_cell_revive(game_space_t *game_space, unsigned int x, unsigned int y);

void change_cell_state(game_space_t *game_space, unsigned int x, unsigned int y);

unsigned char check_cell_state(game_space_t *game_space, unsigned int x, unsigned int y);

game_space_t *copy_game_space(game_space_t *game_space);

void run_iteration(game_space_t *game_space);

void print_game_state(game_space_t *game_space);

void free_game_space(game_space_t *game_space);

void run_game_of_life(game_space_t *game_space, unsigned int snapshot_freq);

#endif //GAME_OF_LIFE_GAME_SPACE_H
