#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include "Drawable.hpp"

namespace gamestate {
    extern bool running;
    extern std::vector<Drawable *> drawings;

    void draw_all(double delta);
}

#endif /* GAMESTATE_H */
