//
// Created by Krzysiek on 27.03.2019.
//

#include <stdio.h>
#include <stdio.h>

#include "game_space_display.h"

void print_game_state(game_space_t *game_space) {
    printf("Iteration %d of %d:\n", game_space->current_iteration, game_space->max_iterations);

    for (int i = 0; i < game_space->y_dim; i++) {
        for (int j = 0; j < game_space->x_dim; j++) {
            printf("%c", game_space->plane[j][i]);
        }
        printf("\n");
    }
}

void render_gif_frame(game_space_t *game_space, uint8_t *frame) {
    for (int y=0; y < game_space->y_dim; y++)
        for (int x=0; x < game_space->x_dim; x++) {
            if (game_space->plane[x][y] == ALIVE) frame[x + y*game_space->x_dim] = 1;
            else frame[x + y*game_space->x_dim] = 0;
        }
}