//
// Created by Krzysztof Piekarczyk on 2019-02-21.
//

#include <stdio.h>
#include "game_space.h"

game_space_t *create_blank_game_space(unsigned int x_dim, unsigned int y_dim, unsigned int iterations) {
    game_space_t *new_space = malloc(sizeof(game_space_t));

    new_space->x_dim = x_dim;
    new_space->y_dim = y_dim;
    new_space->current_iteration = 0;
    new_space->max_iterations = iterations;

    new_space->plane = malloc(sizeof(unsigned char *) * x_dim);

    for (int i = 0; i < x_dim; i++) {
        new_space->plane[i] = malloc(sizeof(unsigned char *) * y_dim);

        for (int j = 0; j < y_dim; j++) {
            new_space->plane[i][j] = DEAD;
        }
    }

    return new_space;
}

void __plane_dimension_guard(game_space_t *game_space, unsigned int x, unsigned int y) {
    if (x >= game_space->x_dim) {
        printf("X index too high! (Indexing starts at 0)");
        exit(EXIT_FAILURE);
    }
    if (y >= game_space->y_dim) {
        printf("Y index too high! (Indexing starts at 0)");
        exit(EXIT_FAILURE);
    }
}

unsigned int count_live_neighbours(game_space_t *game_space, unsigned int x, unsigned int y) {
    __plane_dimension_guard(game_space, x, y);

    unsigned int neigh = 0;

    if (x != 0 && game_space->plane[x - 1][y] == ALIVE) neigh++;
    if (x != game_space->x_dim - 1 && game_space->plane[x + 1][y] == ALIVE) neigh++;

    if (y != 0 && game_space->plane[x][y - 1] == ALIVE) neigh++;
    if (y != game_space->y_dim - 1 && game_space->plane[x][y + 1] == ALIVE) neigh++;

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

void change_cell_state(game_space_t *game_space, unsigned int x, unsigned int y) {
    __plane_dimension_guard(game_space, x, y);

    if (game_space->plane[x][y] == DEAD) game_space->plane[x][y] = ALIVE;
    else game_space->plane[x][y] = DEAD;

}

unsigned char check_cell_state(game_space_t *game_space, unsigned int x, unsigned int y) {
    __plane_dimension_guard(game_space, x, y);

    return game_space->plane[x][y];
}

game_space_t *copy_game_space(game_space_t *game_space) {
    unsigned int x_dim = game_space->x_dim;
    unsigned int y_dim = game_space->y_dim;

    game_space_t *new_space = malloc(sizeof(game_space_t));

    new_space->x_dim = game_space->x_dim;
    new_space->y_dim = game_space->y_dim;
    new_space->current_iteration = game_space->current_iteration;
    new_space->max_iterations = game_space->max_iterations;

    new_space->plane = malloc(sizeof(unsigned char *) * x_dim);

    for (int i = 0; i < x_dim; i++) {
        new_space->plane[i] = malloc(sizeof(unsigned char *) * y_dim);

        for (int j = 0; j < y_dim; j++) {
            new_space->plane[i][j] = game_space->plane[i][j];
        }
    }

    return new_space;
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

void free_game_space(game_space_t *game_space) {
    for (int i = 0; i < game_space->x_dim; i++) {
        free(game_space->plane[i]);
    }
    free(game_space->plane);
    free(game_space);
}

void run_game_of_life(game_space_t *game_space, unsigned int snapshot_freq) {
    printf("Begining Game of Life: %d iterations, snapshot every %d iterations.\n\n", game_space->max_iterations, snapshot_freq);

    print_game_state(game_space);

    while(game_space->current_iteration < game_space->max_iterations) {
        run_iteration(game_space);

        if (game_space->current_iteration % snapshot_freq == 0 || game_space->current_iteration == game_space->max_iterations)
            print_game_state(game_space);
    }

    printf("\n\nGame of Life ended!\n");
}