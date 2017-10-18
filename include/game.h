#ifndef GAME_H_
#define GAME_H_

#include <cstdint>

struct Game {
    const uint32_t screen_width = 640;
    const uint32_t screen_height = 480;
};

int mainloop(Game &game);

#endif //  GAME_H_
