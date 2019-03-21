//
// Created by Krzysztof Piekarczyk on 2019-03-21.
//

#ifndef GAME_OF_LIFE_GAME_SPACE_STRUCT_H
#define GAME_OF_LIFE_GAME_SPACE_STRUCT_H

enum cell_state {DEAD=45, ALIVE=35};
typedef enum bool_e {FALSE, TRUE} bool_t;

typedef struct game_space_s {
    unsigned int x_dim;
    unsigned int y_dim;
    unsigned int current_iteration;
    unsigned int max_iterations;
    unsigned char **plane;
} game_space_t;

#endif //GAME_OF_LIFE_GAME_SPACE_STRUCT_H
