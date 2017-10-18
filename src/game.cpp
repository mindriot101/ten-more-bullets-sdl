#include "game.h"
#include <SDL.h>

/* Static functions */
static int init(Game &game) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Failure to init SDL\n");
        return 1;
    }

    return 0;
}

int mainloop(Game &game) {
    int status = 0;
    status = init(game);
    if (status != 0) {
        return status;
    }
    return 0;
}
