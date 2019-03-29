//
// Created by Krzysztof Piekarczyk on 2019-03-21.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

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

void run_game_of_life__create_a_gif(game_space_t *game_space, char *name, int iter_per_sec) {
    if(iter_per_sec > 60) {
        iter_per_sec = 60;
        printf("WARNING: " GREEN_STR("Iterations per second capped at 60.\n"));
    }

    int frame_delay = (int) ceil((double) 100 / iter_per_sec);
    printf("Begining Game of Life: " GREEN_STR("%d") " iterations.\nNeighborhood: ", game_space->max_iterations);

#ifdef MOORES_NEIGHBOURHOOD
    printf(GREEN_STR("Moore's\n\n"));
#else
    printf(GREEN_STR("Von Neumann's\n\n"));
#endif

    ge_GIF *gif = create_gif(game_space, name);

    render_gif_frame(game_space, gif);

    printf("%d of %d iterations processed.", game_space->current_iteration, game_space->max_iterations);
    fflush(stdout);

    for (int i = 0; i < game_space->max_iterations; i++) {
        run_iteration(game_space);
        render_gif_frame(game_space, gif);
        ge_add_frame(gif, frame_delay);
        printf("\r" GREEN_STR("%d") " of " GREEN_STR("%d") " iterations processed.", game_space->current_iteration,
               game_space->max_iterations);
        fflush(stdout);
    }

    ge_close_gif(gif);
    printf("\n\nGame of Life ended!\n");
}

void run_game_of_life__create_a_gif__timebar(game_space_t *game_space, char *name, int iter_per_sec) {
    if(iter_per_sec > 60) {
        iter_per_sec = 60;
        printf("WARNING: " GREEN_STR("Iterations per second capped at 60.\n"));
    }
    int frame_delay = (int) ceil((double) 100 / iter_per_sec);

    printf("Begining Game of Life: " GREEN_STR("%d") "\nNeighborhood: ", game_space->max_iterations);

#ifdef MOORES_NEIGHBOURHOOD
    printf(GREEN_STR("Moore's\n\n"));
#else
    printf(GREEN_STR("Von Neumann's\n\n"));
#endif

    ge_GIF *gif = create_gif__timebar(game_space, name);

    render_gif_frame(game_space, gif);

    printf("%d of %d iterations processed.", game_space->current_iteration, game_space->max_iterations);
    fflush(stdout);

    for (int i = 0; i < game_space->max_iterations; i++) {
        run_iteration(game_space);
        render_gif_frame__timebar(game_space, gif);
        ge_add_frame(gif, frame_delay);
        printf("\r" GREEN_STR("%d") " of " GREEN_STR("%d") " iterations processed.", game_space->current_iteration,
               game_space->max_iterations);
        fflush(stdout);
    }

    ge_close_gif(gif);
    printf("\n\nGame of Life ended!\n");
}

void run_game_of_life__create_pngs(game_space_t *game_space, unsigned int snapshot_freq) {
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

    render_png(game_space);

    printf("%d of %d iterations processed.", game_space->current_iteration, game_space->max_iterations);
    fflush(stdout);

    while (game_space->current_iteration < game_space->max_iterations) {
        run_iteration(game_space);

        if (game_space->current_iteration % snapshot_freq == 0 ||
            game_space->current_iteration == game_space->max_iterations)
            render_png(game_space);

        printf("\r" GREEN_STR("%d") " of " GREEN_STR("%d") " iterations processed.", game_space->current_iteration,
               game_space->max_iterations);
        fflush(stdout);
    }

    printf("\n\nGame of Life ended!\n");
}