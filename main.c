#include <stdio.h>
#include <stdlib.h>

#include "game_space.h"

#define X_LEN 50
#define Y_LEN 50
#define ITER 50

int main() {
    game_space_t *game_space = create_blank_game_space(X_LEN, Y_LEN, ITER);

    change_cell_state(game_space, 20, 20);
    change_cell_state(game_space, 21, 19);
    change_cell_state(game_space, 21, 21);

    printf("\n\n");

    print_game_state(game_space);

    if (check_cell_state(game_space, 21, 20) == DEAD && does_cell_revive(game_space, 21, 20) == TRUE)
        change_cell_state(game_space, 21, 20);

    game_space->current_iteration++;

    game_space_t *new_space = copy_game_space(game_space);

    print_game_state(new_space);

    free(game_space->plane);
    free(game_space);

    return 0;
}