//
// Created by Krzysiek on 27.03.2019.
//

#include <stdio.h>
#include <stdio.h>
#include <math.h>

#include "game_space_display.h"

void print_game_state(game_space_t *game_space) {
    printf("Iteration %d of %d:\n", game_space->current_iteration, game_space->max_iterations);

    for (int y = 0; y < game_space->y_dim; y++) {
        for (int x = 0; x < game_space->x_dim; x++) {
            printf("%c", game_space->plane[x][y]);
        }
        printf("\n");
    }
}

void render_gif_frame(game_space_t *game_space, uint8_t *frame) {
    for (int y = 0; y < game_space->y_dim; y++) {
        for (int x = 0; x < game_space->x_dim; x++) {
            if (game_space->plane[x][y] == ALIVE) frame[x + y * game_space->x_dim] = 1;
            else frame[x + y * game_space->x_dim] = 0;
        }
    }

    double ratio = (double) game_space->current_iteration / game_space->max_iterations;
    int ready_len = (int) floor(ratio * game_space->x_dim);

    for (int j = 0; j < 5; j++) {
        for (int i = 0; i < game_space->x_dim; i++) {
            if (i < ready_len) frame[i + (game_space->x_dim) + ((game_space->y_dim - 1) * game_space->x_dim) + (j * game_space->x_dim)] = 2;
            else frame[i + (game_space->x_dim) + ((game_space->y_dim - 1) * game_space->x_dim) + (j * game_space->x_dim)] = 3;
        }
    }
}