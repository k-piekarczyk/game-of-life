#ifndef GAME_OF_LIFE_GAME_SPACE_DISPLAY_H
#define GAME_OF_LIFE_GAME_SPACE_DISPLAY_H

#include <stdint.h>

#include "../libs/gifenc/gifenc.h"

#include "game_space_structures.h"

ge_GIF *create_gif__timebar(game_space_t *game_space, char *name);

void render_gif_frame(game_space_t *game_space, ge_GIF *gif);

void render_gif_frame__timebar(game_space_t *game_space, ge_GIF *gif);

void render_png(game_space_t *game_space);

#endif //GAME_OF_LIFE_GAME_SPACE_DISPLAY_H
