#include "utils.h"
#include <cstdio>

void print_sdl_rect(SDL_Rect *rect) {
    printf("<Rect w:%d, h: %d @ (%d, %d)>", rect->w, rect->h, rect->x, rect->y);
}
