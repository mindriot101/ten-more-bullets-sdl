#ifndef GUN_H_
#define GUN_H_

#include "key_press.h"
#include "bullet.h"

#define N_BULLETS 2

struct SDL_Renderer;

struct Gun {
    Gun(int screen_width, int screen_height);
    void update(float dt, bool *key_map);
    void draw(SDL_Renderer *renderer) const;
    void fire(float dt);
    void cleanup();

    Bullet bullets[N_BULLETS];
    bool allocated[N_BULLETS];
    int allocated_bullets = 0;

    bool fired_last_frame = false;
    int bullets_in_flight = 0;

    /* Rendering data */
    SDL_Rect rect_geometry;
    RGBA color = {0xFF, 0x00, 0x00, 0xFF};
};

#endif // GUN_H_
