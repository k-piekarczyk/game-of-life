//
// Created by Krzysztof Piekarczyk on 2019-03-21.
//

#include <stdlib.h>
#include <stdio.h>

#include "game_functions.h"

#if !defined __WIN32 && __WIN64
    #define ANSI_COLOR_GREEN   "\x1b[32m"
    #define ANSI_COLOR_RESET   "\x1b[0m"
#else
    #define ANSI_COLOR_GREEN   ""
    #define ANSI_COLOR_RESET   ""
#endif

#define MOORES_NEIGHBOURHOOD


unsigned int count_live_neighbours(game_space_t *game_space, unsigned int x, unsigned int y) {
    __plane_dimension_guard(game_space, x, y);

    unsigned int neigh = 0;

    if (x != 0 && game_space->plane[x - 1][y] == ALIVE) neigh++;
    if (x != game_space->x_dim - 1 && game_space->plane[x + 1][y] == ALIVE) neigh++;

    if (y != 0 && game_space->plane[x][y - 1] == ALIVE) neigh++;
    if (y != game_space->y_dim - 1 && game_space->plane[x][y + 1] == ALIVE) neigh++;

#ifdef MOORES_NEIGHBOURHOOD
    if (x != 0 && y != 0 && game_space->plane[x - 1][y - 1] == ALIVE) neigh++;
    if (x != 0 && y != game_space->y_dim - 1 && game_space->plane[x - 1][y + 1] == ALIVE) neigh++;

    if (x != game_space->x_dim - 1 && y != 0 && game_space->plane[x + 1][y - 1] == ALIVE) neigh++;
    if (x != game_space->x_dim - 1 && y != game_space->y_dim - 1 && game_space->plane[x + 1][y + 1] == ALIVE) neigh++;
#endif

    return neigh;
}

bool_t does_cell_die(game_space_t *game_space, unsigned int x, unsigned int y) {
    __plane_dimension_guard(game_space, x, y);
    if (game_space->plane[x][y] == DEAD) return FALSE;

    unsigned int live_n = count_live_neighbours(game_space, x, y);

    if (live_n < 2 || live_n > 3) return TRUE;
    else return FALSE;
}

bool_t does_cell_revive(game_space_t *game_space, unsigned int x, unsigned int y) {
    __plane_dimension_guard(game_space, x, y);
    if (game_space->plane[x][y] == ALIVE) return FALSE;

    if (count_live_neighbours(game_space, x, y) == 3) return TRUE;
    else return FALSE;
}

void run_iteration(game_space_t *game_space) {
    unsigned int x_dim = game_space->x_dim;
    unsigned int y_dim = game_space->y_dim;

    game_space_t *lookup_space = copy_game_space(game_space);

    for (unsigned int i = 0; i < x_dim; i++) {
        for (unsigned int j = 0; j < y_dim; j++) {

            if (check_cell_state(lookup_space, i, j) == DEAD) {
                if (does_cell_revive(lookup_space, i, j) == TRUE)
                    change_cell_state(game_space, i, j);
            } else {
                if (does_cell_die(lookup_space, i, j) == TRUE)
                    change_cell_state(game_space, i, j);
            }
        }
    }

    free_game_space(lookup_space);

    game_space->current_iteration++;
}

void print_game_state(game_space_t *game_space) {
    printf("Iteration %d of %d:\n", game_space->current_iteration, game_space->max_iterations);

    for (int i = 0; i < game_space->y_dim; i++) {
        for (int j = 0; j < game_space->x_dim; j++) {
            printf("%c", game_space->plane[j][i]);
        }
        printf("\n");
    }
}


void run_game_of_life(game_space_t *game_space, unsigned int snapshot_freq) {
    printf("Begining Game of Life: " ANSI_COLOR_GREEN "%d" ANSI_COLOR_RESET " iterations, snapshot every " ANSI_COLOR_GREEN "%d" ANSI_COLOR_RESET " iterations.\nNeighborhood: ", game_space->max_iterations,
           snapshot_freq);

#ifdef MOORES_NEIGHBOURHOOD
    printf(ANSI_COLOR_GREEN "Moore's\n\n" ANSI_COLOR_RESET);
#else
    printf(ANSI_COLOR_GREEN "Von Neumann's\n\n" ANSI_COLOR_RESET);
#endif

    print_game_state(game_space);

    while (game_space->current_iteration < game_space->max_iterations) {
        run_iteration(game_space);

        if (game_space->current_iteration % snapshot_freq == 0 ||
            game_space->current_iteration == game_space->max_iterations)
            print_game_state(game_space);
    }

    printf("\n\nGame of Life ended!\n");
}