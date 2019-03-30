#include <stdio.h>
#include <stdlib.h>

#include "game_configuration.h"

int main(int argc, char *argv[]) {

    if (argc < 2) {
        printf("Lack of a configuration file.\n");
        printf("Correct usage: %s <configuration file name>\n", argv[0]);
        printf("\nRead 'https://github.com/k-piekarczyk/game-of-life/blob/master/README.md' for configuration format!\n");
        exit(EXIT_FAILURE);
    }

    run_game_of_life__file(argv[1]);

    return 0;
}