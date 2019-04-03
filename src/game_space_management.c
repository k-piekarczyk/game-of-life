#include <stdio.h>
#include <string.h>
#include "game_space_management.h"


/* DIVIDEND/DIVIDER is the posibility of cell to be alive in randomiser */
#define LIVE_DIVIDEND 1
#define LIVE_DIVIDER 3


game_space_t *create_blank_game_space(unsigned int x_dim, unsigned int y_dim) {
    game_space_t *new_space = malloc(sizeof(game_space_t));

    new_space->x_dim = x_dim;
    new_space->y_dim = y_dim;
    new_space->current_iteration = 0;

    new_space->plane = malloc(sizeof(unsigned char *) * x_dim);

    for (int i = 0; i < x_dim; i++) {
        new_space->plane[i] = malloc(sizeof(unsigned char *) * y_dim);

        for (int j = 0; j < y_dim; j++) {
            new_space->plane[i][j] = DEAD;
        }
    }

    return new_space;
}

void set_max_iterations(game_space_t *game_space, unsigned int iter) {
    game_space->max_iterations = iter;
}

void randomise_game_space(game_space_t *game_space) {
    for (int i = 0; i < game_space->x_dim; i++) {
        for (int j = 0; j < game_space->y_dim; j++) {
            if ((LIVE_DIVIDEND * rand()) % LIVE_DIVIDER == 0) {
                game_space->plane[i][j] = ALIVE;
            }
        }
    }
}

void plane_dimension_guard(game_space_t *game_space, unsigned int x, unsigned int y) {
    if (x >= game_space->x_dim) {
        printf("X index too high! (Indexing starts at 0)");
        exit(EXIT_FAILURE);
    }
    if (y >= game_space->y_dim) {
        printf("Y index too high! (Indexing starts at 0)");
        exit(EXIT_FAILURE);
    }
}

void flip_cell_state(game_space_t *game_space, unsigned int x, unsigned int y) {
    plane_dimension_guard(game_space, x, y);

    if (game_space->plane[x][y] == DEAD) game_space->plane[x][y] = ALIVE;
    else game_space->plane[x][y] = DEAD;

}

unsigned char check_cell_state(game_space_t *game_space, unsigned int x, unsigned int y) {
    plane_dimension_guard(game_space, x, y);

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

void free_game_space(game_space_t *game_space) {
    for (int i = 0; i < game_space->x_dim; i++) {
        free(game_space->plane[i]);
    }
    free(game_space->plane);
    free(game_space);
}