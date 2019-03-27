//
// Created by Krzysztof Piekarczyk on 2019-03-21.
//

#include <stdlib.h>
#include <stdio.h>

#include "../libs/gifenc/gifenc.h"

#include "game_functions.h"
#include "game_space_display.h"

#ifdef __WIN32
#define ANSI_COLOR_GREEN   ""
#define ANSI_COLOR_RESET   ""
#elif defined __WIN64
#define ANSI_COLOR_GREEN   ""
#define ANSI_COLOR_RESET   ""
#else
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#endif

#define GREEN_STR(string) ANSI_COLOR_GREEN string ANSI_COLOR_RESET

#define MOORES_NEIGHBOURHOOD


unsigned int count_live_neighbours(game_space_t *game_space, unsigned int x, unsigned int y) {
    __plane_dimension_guard(game_space, x, y);

    unsigned int neigh = 0;

    if (x != 0 && game_space->plane[x - 1][y] == ALIVE) neigh++;
    if (x != game_space->x_dim - 1 && game_space->plane[x + 1][y] == ALIVE) neigh++;

    if (y != 0 && game_space->plane[x][y - 1] == ALIVE) neigh++;
    if (y != game_space->y_dim - 1 && game_space->plane[x][y + 1] == ALIVE) neigh++;

#ifdef MOORES_NEIGHBOURHOOD
    if (x != 0 && y != 0 && game_space->plane[x - 1][y - 1] == ALIVE) neigh++;
    if (x != 0 && y != game_space->y_dim - 1 && game_space->plane[x - 1][y + 1] == ALIVE) neigh++;

    if (x != game_space->x_dim - 1 && y != 0 && game_space->plane[x + 1][y - 1] == ALIVE) neigh++;
    if (x != game_space->x_dim - 1 && y != game_space->y_dim - 1 && game_space->plane[x + 1][y + 1] == ALIVE) neigh++;
#endif

    return neigh;
}

bool_t does_cell_die(game_space_t *game_space, unsigned int x, unsigned int y) {
    __plane_dimension_guard(game_space, x, y);
    if (game_space->plane[x][y] == DEAD) return FALSE;

    unsigned int live_n = count_live_neighbours(game_space, x, y);

    if (live_n < 2 || live_n > 3) return TRUE;
    else return FALSE;
}

bool_t does_cell_revive(game_space_t *game_space, unsigned int x, unsigned int y) {
    __plane_dimension_guard(game_space, x, y);
    if (game_space->plane[x][y] == ALIVE) return FALSE;

    if (count_live_neighbours(game_space, x, y) == 3) return TRUE;
    else return FALSE;
}

void run_iteration(game_space_t *game_space) {
    unsigned int x_dim = game_space->x_dim;
    unsigned int y_dim = game_space->y_dim;

    game_space_t *lookup_space = copy_game_space(game_space);

    for (unsigned int i = 0; i < x_dim; i++) {
        for (unsigned int j = 0; j < y_dim; j++) {

            if (check_cell_state(lookup_space, i, j) == DEAD) {
                if (does_cell_revive(lookup_space, i, j) == TRUE)
                    change_cell_state(game_space, i, j);
            } else {
                if (does_cell_die(lookup_space, i, j) == TRUE)
                    change_cell_state(game_space, i, j);
            }
        }
    }

    free_game_space(lookup_space);

    game_space->current_iteration++;
}


void run_game_of_life__display_to_console(game_space_t *game_space, unsigned int snapshot_freq) {
    printf("Begining Game of Life: "
           GREEN_STR("%d")
           " iterations, snapshot every "
           GREEN_STR("%d")
           " iterations.\nNeighborhood: ", game_space->max_iterations,
           snapshot_freq);

#ifdef MOORES_NEIGHBOURHOOD
    printf(GREEN_STR("Moore's\n\n"));
#else
    printf(GREEN_STR("Von Neumann's\n\n"));
#endif

    print_game_state(game_space);

    while (game_space->current_iteration < game_space->max_iterations) {
        run_iteration(game_space);

        if (game_space->current_iteration % snapshot_freq == 0 ||
            game_space->current_iteration == game_space->max_iterations)
            print_game_state(game_space);
    }

    printf("\n\nGame of Life ended!\n");
}

void run_game_of_life__create_a_gif(game_space_t *game_space) {
    printf("Begining Game of Life: " GREEN_STR("%d") "\nNeighborhood: ", game_space->max_iterations);

#ifdef MOORES_NEIGHBOURHOOD
    printf(GREEN_STR("Moore's\n\n"));
#else
    printf(GREEN_STR("Von Neumann's\n\n"));
#endif

    ge_GIF *gif = ge_new_gif("game_of_life.gif", game_space->x_dim, game_space->y_dim,
                             (uint8_t[]) {0xFF, 0xFF, 0xFF, /* 0 -> white */ 0x00, 0x00, 0x00  /* 1 -> black */}, 1, 0);

    render_gif_frame(game_space, gif->frame);

    for (int i = 0; i < game_space->max_iterations; i++) {
        run_iteration(game_space);
        render_gif_frame(game_space, gif->frame);
        ge_add_frame(gif, 10);
    }

    ge_close_gif(gif);
    printf("\n\nGame of Life ended!\n");
}