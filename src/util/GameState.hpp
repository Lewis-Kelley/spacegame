#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include "../drawables/Drawable.hpp"

namespace gamestate {
    extern std::vector<Drawable *> drawings;
    extern int tile_size;
    extern bool running;

    void draw_all(double delta);
}

#endif /* GAMESTATE_H */
