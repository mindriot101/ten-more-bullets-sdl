#ifndef KEY_PRESS_H_
#define KEY_PRESS_H_

#include <cstdint>

enum struct KeyPress {
    Default,
    Up,
    Down,
    Left,
    Right,
    Fire,
    TOTAL,
};

uint32_t press_to_index(KeyPress press);

#endif // KEY_PRESS_H_
