#include "gun.h"
#include <cassert>

Gun::Gun() {
    for (auto i=0; i<N_BULLETS; i++) {
        allocated[i] = false;
    }
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
