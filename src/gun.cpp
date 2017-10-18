#include "gun.h"

void Gun::update(float dt, bool *key_map) {
    bool fire_pressed = key_map[press_to_index(KeyPress::Fire)];
    if (fire_pressed && !fired_last_frame) {
        bullets_in_flight += 1;
        fired_last_frame = true;
    }

    if (fired_last_frame && !fire_pressed) {
        fired_last_frame = false;
    }

    printf("BULLETS IN FLIGHT: %d\n", bullets_in_flight);
}
