//
// Created by Krzysiek on 27.03.2019.
//

#ifndef GAME_OF_LIFE_GAME_SPACE_DISPLAY_H
#define GAME_OF_LIFE_GAME_SPACE_DISPLAY_H

#include <stdint.h>
#include "game_space_structures.h"

void print_game_state(game_space_t *game_space);
void render_gif_frame(game_space_t *game_space, uint8_t *frame);

#endif //GAME_OF_LIFE_GAME_SPACE_DISPLAY_H
