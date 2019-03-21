#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game_space_management.h"

#define X_LEN 30
#define Y_LEN 10
#define ITER 10

int main() {
    srand(time(NULL));

    game_space_t *game_space = create_blank_game_space(X_LEN, Y_LEN, ITER);

    randomise_game_space(game_space);

    run_game_of_life(game_space, 1);

    free_game_space(game_space);

    return 0;
}