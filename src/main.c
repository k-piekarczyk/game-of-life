#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "game_space_management.h"
#include "game_space_display.h"
#include "game_space_structures.h"
#include "game_functions.h"
#include "game_configuration.h"

#define X_LEN 1000
#define Y_LEN 500
#define ITER 500

int main(int argc, char *argv[]) {
    int option;

//    if (argc == 1) {
//        printf("Choose an option:\n");
//        printf("\t1 - configuration from a file\n");
//        printf("\t2 - configuration from a png + file\n");
//        printf("Option: ");
//        scanf("%d", &option);
//    }

    run_game_of_life__file("gol.conf");

    return 0;
}

//    srand(time(NULL));

//    game_space_t *game_space= create_blank_game_space(X_LEN, Y_LEN);
//    game_space_t *game_space = create_game_of_life__png("input.png");
//    set_max_iterations(game_space, ITER);
//    run_game_of_life__display_to_console(game_space, 15);
//    run_game_of_life__create_a_gif(game_space, "game_of_life.gif", 60);
//    run_game_of_life__create_a_gif__timebar(game_space, "game_of_life.gif", 60);
//    run_game_of_life__create_pngs(game_space, 50);
//    free_game_space(game_space);