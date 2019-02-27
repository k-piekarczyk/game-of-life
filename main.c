#include <stdio.h>
#include <stdlib.h>

#include "game_space.h"

#define X_LEN 50
#define Y_LEN 50
#define ITER 10

int main() {
    game_space_t *game_space = create_blank_game_space(X_LEN, Y_LEN, ITER);

    change_cell_state(game_space, 0, 0);

    run_game_of_life(game_space, 1);

    free_game_space(game_space);

    return 0;
}