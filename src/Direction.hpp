#ifndef DIRECTION_H
#define DIRECTION_H

enum Direction {
    EAST = 0,
    NORTH = 1,
    WEST = 2,
    SOUTH = 3,
    NO_DIRECTION
};

Direction opp_dir(Direction dir);

#endif /* DIRECTION_H */
