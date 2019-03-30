//
// Created by Krzysztof Piekarczyk on 2019-02-21.
//

#include <stdio.h>
#include <string.h>
#include "game_space_management.h"


/* DIVIDEND/DIVIDER is the posibility of cell to be alive in randomiser */
#define LIVE_DIVIDEND 1
#define LIVE_DIVIDER 3
#define LINE_BUFFER 256


game_space_t *create_blank_game_space(unsigned int x_dim, unsigned int y_dim, unsigned int iterations) {
    game_space_t *new_space = malloc(sizeof(game_space_t));

    new_space->x_dim = x_dim;
    new_space->y_dim = y_dim;
    new_space->current_iteration = 0;
    new_space->max_iterations = iterations;

    new_space->plane = malloc(sizeof(unsigned char *) * x_dim);

    for (int i = 0; i < x_dim; i++) {
        new_space->plane[i] = malloc(sizeof(unsigned char *) * y_dim);

        for (int j = 0; j < y_dim; j++) {
            new_space->plane[i][j] = DEAD;
        }
    }

    return new_space;
}

void randomise_game_space(game_space_t *game_space) {
    for (int i = 0; i < game_space->x_dim; i++) {
        for (int j = 0; j < game_space->y_dim; j++) {
            if ((LIVE_DIVIDEND * rand()) % LIVE_DIVIDER == 0) {
                game_space->plane[i][j] = ALIVE;
            }
        }
    }
}

void fill_game_space(game_space_t *game_space, int *tabAlive[100], int numAlive) {
    for (int i = 0; i < numAlive; i++) {
        if (tabAlive[0][i] < game_space->x_dim && tabAlive[1][i] < game_space->y_dim) {
            game_space->plane[(tabAlive[0][i])][(tabAlive[1][i])] = ALIVE;
        }
    }
}

void __plane_dimension_guard(game_space_t *game_space, unsigned int x, unsigned int y) {
    if (x >= game_space->x_dim) {
        printf("X index too high! (Indexing starts at 0)");
        exit(EXIT_FAILURE);
    }
    if (y >= game_space->y_dim) {
        printf("Y index too high! (Indexing starts at 0)");
        exit(EXIT_FAILURE);
    }
}

void change_cell_state(game_space_t *game_space, unsigned int x, unsigned int y) {
    __plane_dimension_guard(game_space, x, y);

    if (game_space->plane[x][y] == DEAD) game_space->plane[x][y] = ALIVE;
    else game_space->plane[x][y] = DEAD;

}

unsigned char check_cell_state(game_space_t *game_space, unsigned int x, unsigned int y) {
    __plane_dimension_guard(game_space, x, y);

    return game_space->plane[x][y];
}

game_space_t *copy_game_space(game_space_t *game_space) {
    unsigned int x_dim = game_space->x_dim;
    unsigned int y_dim = game_space->y_dim;

    game_space_t *new_space = malloc(sizeof(game_space_t));

    new_space->x_dim = game_space->x_dim;
    new_space->y_dim = game_space->y_dim;
    new_space->current_iteration = game_space->current_iteration;
    new_space->max_iterations = game_space->max_iterations;

    new_space->plane = malloc(sizeof(unsigned char *) * x_dim);

    for (int i = 0; i < x_dim; i++) {
        new_space->plane[i] = malloc(sizeof(unsigned char *) * y_dim);

        for (int j = 0; j < y_dim; j++) {
            new_space->plane[i][j] = game_space->plane[i][j];
        }
    }

    return new_space;
}

void free_game_space(game_space_t *game_space) {
    for (int i = 0; i < game_space->x_dim; i++) {
        free(game_space->plane[i]);
    }
    free(game_space->plane);
    free(game_space);
}


game_space_t *create_game_space(char *fileName) {
    int y = 100, x = 100, iterations = 10, random = 1;
    int *tabAlive[100];
        for(int i =0; i < 100; i++){
            tabAlive[i] = (int *)malloc(2 * sizeof(int));
        }
    int numAlive = 0;
    char *token;
    FILE *fp;
    fp = fopen(fileName, "r");
    if (fp == NULL) {
        printf("No file '%s'.\n", fileName);
    } else {
        char line[LINE_BUFFER];
        while (fgets(line, sizeof line, fp) != NULL) {
            token = strtok(line, "<,;>");
            if ((strstr(token, "Dimensions")) != NULL) {
                token = strtok(NULL, "<,>");
                if (token != NULL) {
                    x = strtol(token, NULL, 10);
                    if (x == 0) {
                        printf("Dimension x error");
                        exit(EXIT_FAILURE);
                    }
                }
                token = strtok(NULL, ",");
                if (token != NULL) {
                    y = strtol(token, NULL, 10);
                    if (y == 0) {
                        printf("Dimension y error");
                        exit(EXIT_FAILURE);
                    }
                }
            }
            if ((strstr(token, "Iterations")) != NULL) {
                token = strtok(NULL, "<,>");
                if (token != NULL) {
                    iterations = strtol(token, NULL, 10);
                }
            }
            if ((strstr(token, "Alive")) != NULL) {
                random = 0;
                token = strtok(NULL, "<,;>");
                while (token != NULL && numAlive < 100) {
                    tabAlive[0][numAlive] = strtol(token, NULL, 10);
                    token = strtok(NULL, ";,");
                    if (token != NULL) {
                        tabAlive[1][numAlive] = strtol(token, NULL, 10);
                    }
                    token = strtok(NULL, ";,");
                    numAlive++;
                }
            }

        }
    }
    game_space_t *game_space = create_blank_game_space(x, y, iterations);
    if (random == 1) {
        randomise_game_space(game_space);
    } else {
        fill_game_space(game_space, tabAlive, numAlive);
    }
    return game_space;
}



