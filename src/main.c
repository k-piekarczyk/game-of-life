#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game_space_management.h"
#include "game_space_structures.h"
#include "game_functions.h"

#define X_LEN 400
#define Y_LEN 400
#define ITER 500

int main() {
    srand(time(NULL));

    game_space_t *game_space = create_blank_game_space(X_LEN, Y_LEN, ITER);

    randomise_game_space(game_space);

//    run_game_of_life__display_to_console(game_space, 1);
    run_game_of_life__create_a_gif(game_space);

    free_game_space(game_space);

    return 0;
}