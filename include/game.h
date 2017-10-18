#ifndef GAME_H_
#define GAME_H_

#include <cstdint>
#include <SDL.h>
#include "color.h"
#include "rectangle.h"

struct Game {
    const int screen_width = 640;
    const int screen_height = 480;
    const float simulation_dt = 0.016f;     // 60FPS update rate
    const RGBA clear_color = {0x32, 0x4C, 0x32, 0xFF};

    ~Game();

    int update(float dt);
    int draw() const;
    void clear() const;
    void blit() const;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    bool running = true;

    /* Entities */
    Rectangle rectangles[256];
    int allocated_rectangles = 0;
};

int mainloop(Game &game);

#endif //  GAME_H_
