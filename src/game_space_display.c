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