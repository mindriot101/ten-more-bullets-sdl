#ifndef GAME_H_
#define GAME_H_

#include <cstdint>
#include <SDL.h>

struct Game {
    const uint32_t screen_width = 640;
    const uint32_t screen_height = 480;

    ~Game();

    SDL_Window *window;
    // SDL_GLContext gl_context;
    bool running;
};

int mainloop(Game &game);

#endif //  GAME_H_
