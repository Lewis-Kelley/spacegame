#ifndef DIRECTION_H
#define DIRECTION_H

#include <stdio.h>

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
bool has_direction(Direction checked_dir, Direction goal_dir);
bool is_cardinal_dir(Direction dir);
bool is_horiz_dir(Direction dir);
Direction merge_directions(Direction dirA, Direction dirB);
Direction remove_direction(Direction base_dir, Direction dir_to_rem);

#endif /* DIRECTION_H */
