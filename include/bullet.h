#ifndef BULLET_H_
#define BULLET_H_

#include "rectangle.h"

struct Bullet {
    Rectangle rect;
    bool active = false;
};

#endif // BULLET_H_
