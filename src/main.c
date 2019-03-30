#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game_space_management.h"
#include "game_space_display.h"
#include "game_space_structures.h"
#include "game_functions.h"

#define X_LEN 1000
#define Y_LEN 500
#define ITER 5

int main(int argc, char *argv[]) {
    srand(time(NULL));

    game_space_t *game_space=create_game_space(argv[1]);
    if (argc>3) {
        int run, num;
        run = atoi(argv[2]);
        num = atoi(argv[3]);

        if(run==1) run_game_of_life__display_to_console(game_space, num);
        if(run==2) run_game_of_life__create_a_gif(game_space, "game_of_life.gif", num);
        if(run==3) run_game_of_life__create_a_gif__timebar(game_space, "game_of_life.gif", num);
        if(run==4) run_game_of_life__create_pngs(game_space, num);
    }
    free_game_space(game_space);


    return 0;
}