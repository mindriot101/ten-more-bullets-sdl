#include "game.h"
#include "key_press.h"
#include "rectangle.h"
#include <cstdlib>

static bool KeyMap[static_cast<uint32_t>(KeyPress::TOTAL)];

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

    if (game.window == nullptr) {
        fprintf(stderr, "Error creating window. SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    game.renderer = SDL_CreateRenderer(game.window, -1, SDL_RENDERER_ACCELERATED);
    if (game.renderer == nullptr) {
        fprintf(stderr, "Error creating renderer. SDL_Error: %s\n", SDL_GetError());
        return 1;
    }

    for (uint32_t i=0; i<press_to_index(KeyPress::TOTAL); i++) {
        KeyMap[i] = false;
    }

    game.gun = new Gun(game.screen_width, game.screen_height);

    return 0;
}

Game::~Game() {
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int handle_event(Game &game, SDL_Event &event) {
    if (event.type == SDL_QUIT) {
        game.running = false;
    } else if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
            case SDLK_ESCAPE:
                {
                game.running = false;
                break;
                }
            case SDLK_SPACE:
                {
                KeyMap[press_to_index(KeyPress::Fire)] = true;
                break;
                }
            case SDLK_UP:
                {
                KeyMap[press_to_index(KeyPress::Up)] = true;
                break;
                }
            case SDLK_DOWN:
                {
                KeyMap[press_to_index(KeyPress::Down)] = true;
                break;
                }
            case SDLK_LEFT:
                {
                KeyMap[press_to_index(KeyPress::Left)] = true;
                break;
                }
            case SDLK_RIGHT:
                {
                KeyMap[press_to_index(KeyPress::Right)] = true;
                break;
                }
        }
    } else if (event.type == SDL_KEYUP) {
        switch (event.key.keysym.sym) {
            case SDLK_SPACE:
                {
                KeyMap[press_to_index(KeyPress::Fire)] = false;
                break;
                }
            case SDLK_UP:
                {
                KeyMap[press_to_index(KeyPress::Up)] = false;
                break;
                }
            case SDLK_DOWN:
                {
                KeyMap[press_to_index(KeyPress::Down)] = false;
                break;
                }
            case SDLK_LEFT:
                {
                KeyMap[press_to_index(KeyPress::Left)] = false;
                break;
                }
            case SDLK_RIGHT:
                {
                KeyMap[press_to_index(KeyPress::Right)] = false;
                break;
                }
        }
    }

    return 0;
}

int Game::update(float dt) {
    gun->update(dt, KeyMap);
    return 0;
}

void Game::clear() const {
    SDL_SetRenderDrawColor(renderer,
            clear_color.r,
            clear_color.g,
            clear_color.b,
            clear_color.a);
    SDL_RenderClear(renderer);
}

void Game::blit() const {
    SDL_RenderPresent(renderer);
}

int Game::draw() const {
    clear();

    gun->draw(renderer);

    blit();
    return 0;
}


#define CHECKED(expr) { int status = expr; if (status != 0) return status; }

int mainloop(Game &game) {
    CHECKED(init(game));

    SDL_Event event;
    uint64_t old_ticks = 0;
    float accumulator = 0.0f;

    while (game.running) {
        uint64_t now = SDL_GetPerformanceCounter();
        float dt = (now - old_ticks) / (float)SDL_GetPerformanceFrequency();
        old_ticks = now;

        /* The game update took too long e.g. the window was not focused */
        if (dt > 0.1f) {
            dt = game.simulation_dt;
        }

        while (SDL_PollEvent(&event)) {
            CHECKED(handle_event(game, event));
        }

        accumulator += dt;
        while (accumulator >= game.simulation_dt) {
            CHECKED(game.update(accumulator));
            accumulator -= game.simulation_dt;
        }

        CHECKED(game.draw());
    }

    return 0;
}
