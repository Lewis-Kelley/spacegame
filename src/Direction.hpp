#ifndef DIRECTION_H
#define DIRECTION_H

enum Direction {
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
int index_value(Direction dir);

#endif /* DIRECTION_H */
