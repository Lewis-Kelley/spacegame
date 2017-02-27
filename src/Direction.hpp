#ifndef DIRECTION_H
#define DIRECTION_H

#include <stdio.h>

enum Direction {
    // EAST = 0,
    // NORTH = 1,
    // WEST = 2,
    // SOUTH = 3,
    // NO_DIRECTION
    NO_DIRECTION = 0,
    EAST = 1,
    NORTH = 2,
    WEST = 4,
    SOUTH = 8,
    NORTH_EAST = NORTH | EAST,
    NORTH_WEST = NORTH | WEST,
    SOUTH_WEST = SOUTH | WEST,
    SOUTH_EAST = SOUTH | EAST
};

Direction opp_dir(Direction dir);
void print_dir(Direction dir);

#endif /* DIRECTION_H */
