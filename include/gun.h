#ifndef GUN_H_
#define GUN_H_

#include "key_press.h"
#include "bullet.h"

struct Gun {
    void update(float dt, bool *key_map);

    Bullet bullets[256];
    int allocated_bullets = 0;

    bool fired_last_frame = false;
    int bullets_in_flight = 0;
};

#endif // GUN_H_
