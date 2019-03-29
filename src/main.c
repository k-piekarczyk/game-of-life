#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game_space_management.h"
#include "game_space_display.h"
#include "game_space_structures.h"
#include "game_functions.h"

#define X_LEN 1000
#define Y_LEN 500
#define ITER 500

int main() {
    srand(time(NULL));

    game_space_t *game_space = create_blank_game_space(X_LEN, Y_LEN, ITER);

    randomise_game_space(game_space);

//    run_game_of_life__display_to_console(game_space, 1);
//    run_game_of_life__create_a_gif(game_space, "game_of_life.gif", 25);
//    run_game_of_life__create_a_gif__timebar(game_space, "game_of_life.gif", 61);
    run_game_of_life__create_pngs(game_space, 50);

    free_game_space(game_space);


    return 0;
}