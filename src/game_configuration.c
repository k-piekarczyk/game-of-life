//
// Created by Krzysztof Piekarczyk on 2019-03-30.
//

#include <stdio.h>

#include "../libs/lodepng/lodepng.h"

#include "game_configuration.h"
#include "game_space_management.h"

game_space_t *create_game_of_life__png(char *file_name) {
    unsigned error;
    unsigned char *image;
    unsigned width, height;

    error = lodepng_decode32_file(&image, &width, &height, file_name);
    if (error) printf("error %u: %s\n", error, lodepng_error_text(error));

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