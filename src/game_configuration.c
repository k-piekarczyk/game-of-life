//
// Created by Krzysztof Piekarczyk on 2019-03-30.
//

#include <stdio.h>
#include <time.h>

#include "../libs/lodepng/lodepng.h"

#include "game_configuration.h"
#include "game_space_management.h"
#include "game_functions.h"

#define SUB_BUFFER 256
#define LINE_BUFFER 256

typedef struct parsed_line_s {
    char *key;
    char *value;
} parsed_line_t;

game_space_t *create_game_of_life__png(char *file_name) {
    unsigned error;
    unsigned char *image;
    unsigned width, height;

    error = lodepng_decode32_file(&image, &width, &height, file_name);
    if (error) {
        printf("No file with name: %s!\n", file_name);
        exit(EXIT_FAILURE);
    }

    game_space_t *new_space = create_blank_game_space(width, height);

    int temp;
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            temp = 4 * width * y + 4 * x;
            if (image[temp + 0] == 0 && image[temp + 1] == 0 && image[temp + 2] == 0 && image[temp + 3] == 255) {
                new_space->plane[x][y] = ALIVE;
            } else {
                new_space->plane[x][y] = DEAD;
            }
        }
    }

    free(image);
    return new_space;
}

parsed_line_t *parse_line(const char *src) {
    char *bufor[SUB_BUFFER];
    char *line = malloc(strlen(src) + 1);
    strcpy(line, src);
    char *token;


    char *ptr = strtok(line, ">");
    token = ptr;
    ptr = strtok(NULL, ">");

    parsed_line_t *parsed_line = malloc(sizeof(parsed_line_t));
    parsed_line->key = token;
    parsed_line->value = ptr;

    return parsed_line;
}

void run_game_of_life__file(char *file_name) {
    int width = 0, height = 0, max_iter = 0, freq = 0, fps = 0;
    char *png = NULL;
    bool_t config_done = FALSE, config_alive = FALSE;

    FILE *fp;
    char line[LINE_BUFFER];
    parsed_line_t *parsed_line;

    fp = fopen(file_name, "r");
    if (fp == NULL) {
        printf("No file '%s'.\n", file_name);
        exit(EXIT_FAILURE);
    }

    while (fgets(line, sizeof line, fp) != NULL) {
        strtok(line, "\n");
        parsed_line = parse_line(line);

        if (strcmp("png", parsed_line->key) == 0) {
            png = parsed_line->value;
        } else if (strcmp("width", parsed_line->key) == 0) {
            width = atoi(parsed_line->value);
        } else if (strcmp("height", parsed_line->key) == 0) {
            height = atoi(parsed_line->value);
        } else if (strcmp("max_iter", parsed_line->key) == 0) {
            max_iter = atoi(parsed_line->value);
        } else if (strcmp("freq", parsed_line->key) == 0) {
            freq = atoi(parsed_line->value);
        } else if (strcmp("fps", parsed_line->key) == 0) {
            fps = atoi(parsed_line->value);
        }

        if (((width > 0 && height > 0) || png != NULL) && max_iter > 0 && (freq > 0 || fps > 0)) {
            config_done = TRUE;
            break;
        }
    }

    if (config_done == FALSE) {
        printf("Configuration incomplete! Required values:\n");
        printf("\t- height\n");
        printf("\t- width\n");
        printf("\t- png <instead of height and width>\n");
        printf("\t- max_iter\n");
        printf("\t- freq or fps\n");
        exit(EXIT_FAILURE);
    }

    game_space_t *game_space;
    if (png != NULL) {
        game_space = create_game_of_life__png(png);
    } else {
        game_space = create_blank_game_space(width, height);

        rewind(fp);
        char *tmp_x, *tmp_y;
        while (fgets(line, sizeof line, fp) != NULL) {
            strtok(line, "\n");
            parsed_line = parse_line(line);

            if (strcmp("alive", parsed_line->key) == 0) {
                tmp_x = strtok(parsed_line->value, ",");
                tmp_y = strtok(NULL, ",");

                change_cell_state(game_space, atoi(tmp_x), atoi(tmp_y));
                config_alive = TRUE;
            }
        }

        if (config_alive == FALSE) {
            srand(time(NULL));
            randomise_game_space(game_space);
        }
    }

    set_max_iterations(game_space, max_iter);

    if (freq > 0) {
        run_game_of_life__create_pngs(game_space, freq);
    } else if (fps > 0) {
        run_game_of_life__create_a_gif__timebar(game_space, "out/gol_output.gif", fps);
    }

    free_game_space(game_space);
}