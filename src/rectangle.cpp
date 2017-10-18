#include "rectangle.h"

SDL_Rect Rectangle::to_sdl_rect() const {
    SDL_Rect rect = { (int)x, (int)y, width, height };
    return rect;
}

void Rectangle::draw(SDL_Renderer *renderer) const {
    SDL_Rect fill_rect = to_sdl_rect();
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &fill_rect);
}
