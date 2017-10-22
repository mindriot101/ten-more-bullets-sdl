#include "gun.h"
#include "utils.h"
#include <cassert>

Gun::Gun(int screen_width, int screen_height) {
    for (auto i=0; i<N_BULLETS; i++) {
        allocated[i] = false;
    }

    /* Set up rendering data */
    rect_geometry.w = 20;
    rect_geometry.h = 20;
    rect_geometry.x = screen_width / 2;
    rect_geometry.y = screen_height - rect_geometry.h;

    printf("GEOMETRY: ");
    print_sdl_rect(&rect_geometry);
}

void Gun::update(float dt, bool *key_map) {
    bool fire_pressed = key_map[press_to_index(KeyPress::Fire)];

    /* De-bounce the firing */
    if (fire_pressed && !fired_last_frame) {
        fire(dt);
        fired_last_frame = true;
    }

    if (fired_last_frame && !fire_pressed) {
        fired_last_frame = false;
    }

    cleanup();
}

void Gun::draw(SDL_Renderer *renderer) const {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRect(renderer, &rect_geometry);
}

void Gun::fire(float dt) {
    printf("Firing\n");
    if (allocated_bullets == (N_BULLETS - 1)) {
        assert(0);
    }

    /* Allocate a new bullet */
    for (int i=0; i<N_BULLETS; i++) {
        if (!allocated[i]) {
            allocated[i] = true;
            allocated_bullets += 1;
            bullets_in_flight += 1;
            break;
        }
    }
}

/* Remove all bullets that have left the screen */
void Gun::cleanup() {
}
