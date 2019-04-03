//
// Created by Krzysiek on 27.03.2019.
//

#include <stdio.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#include "./../libs/lodepng/lodepng.h"

#include "game_space_display.h"

#define TIMEBAR_HEIGHT 5

uint8_t color_palette[] = {
        0xFF, 0xFF, 0xFF, /* 0 -> white */
        0x00, 0x00, 0x00, /* 1 -> black */
        0xFF, 0x00, 0x00, /* 2 -> red */
        0x00, 0x00, 0xFF, /* 3 -> blue */
};

ge_GIF *create_gif__timebar(game_space_t *game_space, char *name) {
    return ge_new_gif(name, game_space->x_dim, game_space->y_dim + TIMEBAR_HEIGHT, color_palette, 2, 0);
}

void render_gif_frame(game_space_t *game_space, ge_GIF *gif) {
    for (int y = 0; y < game_space->y_dim; y++) {
        for (int x = 0; x < game_space->x_dim; x++) {
            if (game_space->plane[x][y] == ALIVE) gif->frame[x + y * game_space->x_dim] = 1;
            else gif->frame[x + y * game_space->x_dim] = 0;
        }
    }
}

void render_gif_frame__timebar(game_space_t *game_space, ge_GIF *gif) {
    if (gif->h < game_space->y_dim + TIMEBAR_HEIGHT) {
        printf("\n\nGIF dimensions too small to fit a timebar!");
        exit(EXIT_FAILURE);
    }

    for (int y = 0; y < game_space->y_dim; y++) {
        for (int x = 0; x < game_space->x_dim; x++) {
            if (game_space->plane[x][y] == ALIVE) gif->frame[x + y * game_space->x_dim] = 1;
            else gif->frame[x + y * game_space->x_dim] = 0;
        }
    }

    double ratio = (double) game_space->current_iteration / game_space->max_iterations;
    int ready_len = (int) floor(ratio * game_space->x_dim);

    for (int j = 0; j < TIMEBAR_HEIGHT; j++) {
        for (int i = 0; i < game_space->x_dim; i++) {
            if (i < ready_len)
                gif->frame[i + (game_space->x_dim) + ((game_space->y_dim - 1) * game_space->x_dim) +
                           (j * game_space->x_dim)] = 2;
            else
                gif->frame[i + (game_space->x_dim) + ((game_space->y_dim - 1) * game_space->x_dim) +
                           (j * game_space->x_dim)] = 3;
        }
    }
}

void __encodePNG(const char *filename, const unsigned char *image, unsigned width, unsigned height) {
    /*Encode the image*/
    unsigned error = lodepng_encode32_file(filename, image, width, height);

    /*if there's an error, display it*/
    if (error) {
        printf("\n\nAn error occured while writing file: %s!\n", filename);
        exit(EXIT_FAILURE);
    }
}

void render_png(game_space_t *game_space) {
    char *file_name = (char *) malloc(128 * sizeof(char));
    sprintf(file_name, "out/iter_%d.png", game_space->current_iteration);

    unsigned width = game_space->x_dim, height = game_space->y_dim;
    unsigned char *image = malloc(width * height * 4);
    unsigned x, y;

    for (y = 0; y < height; y++)
        for (x = 0; x < width; x++) {
            if (game_space->plane[x][y] == ALIVE) {
                image[4 * width * y + 4 * x + 0] = 0; /* R */
                image[4 * width * y + 4 * x + 1] = 0; /* G */
                image[4 * width * y + 4 * x + 2] = 0; /* B */
                image[4 * width * y + 4 * x + 3] = 255; /* A */
            } else {
                image[4 * width * y + 4 * x + 0] = 255; /* R */
                image[4 * width * y + 4 * x + 1] = 255; /* G */
                image[4 * width * y + 4 * x + 2] = 255; /* B */
                image[4 * width * y + 4 * x + 3] = 255; /* A */
            }
        }

    __encodePNG(file_name, image, width, height);
    free(image);
}