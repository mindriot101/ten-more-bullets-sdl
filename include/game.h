#ifndef GAME_H_
#define GAME_H_

#include <cstdint>
#include <SDL.h>
#include "color.h"

struct Game {
    const uint32_t screen_width = 640;
    const uint32_t screen_height = 480;
    const float simulation_dt = 0.016f;     // 60FPS update rate
    const RGBA clear_color = {0x32, 0x4C, 0x32, 0xFF};

    ~Game();

    void clear() const;
    void blit() const;

    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    bool running = true;
};

int mainloop(Game &game);

#endif //  GAME_H_
