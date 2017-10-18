#ifndef RECTANGLE_H_
#define RECTANGLE_H_

#include <SDL.h>
#include "color.h"

struct Rectangle {
    int width, height;
    float x, y;
    RGBA color;

    void draw(SDL_Renderer *renderer) const;
    SDL_Rect to_sdl_rect() const;
};

#endif // RECTANGLE_H_
