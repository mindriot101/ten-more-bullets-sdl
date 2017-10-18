#include "game.h"

/* Static functions */
static int init(Game &game) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        fprintf(stderr, "Failure to init SDL\n");
        return 1;
    }

    /* Set up SDL OpenGL parameters */
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
    SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 4);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

    game.window = SDL_CreateWindow("10 More Bullets",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            game.screen_width,
            game.screen_height,
            SDL_WINDOW_SHOWN);

    game.running = true;

    return 0;
}

Game::~Game() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int handle_event(Game &game, SDL_Event &event) {
    if (event.type == SDL_QUIT) {
        game.running = false;
    }
    return 0;
}

int mainloop(Game &game) {
    int status = 0;
    status = init(game);
    if (status != 0) return status;

    SDL_Event event;
    uint64_t old_ticks = 0;

    while (game.running) {
        uint64_t now = SDL_GetPerformanceCounter();
        float dt = (now - old_ticks) / (float)SDL_GetPerformanceFrequency();
        old_ticks = now;

        while (SDL_PollEvent(&event)) {
            status = handle_event(game, event);
            if (status != 0) return status;
        }
    }

    return 0;
}
