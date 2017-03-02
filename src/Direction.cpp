#include "Direction.hpp"

/**
 * Returns the direction in the opposite...direction from the passed
 * direction.
 *
 * @param dir The base Direction.
 * @return The Direction opposite dir
 */
Direction opp_dir(Direction dir)
{
    int shifted = dir << 2;
    return (Direction)((shifted & 0b1100) + (shifted >> 4));
}

int index_value(Direction dir)
{
    switch (dir) {
    case EAST:
        return 0;
    case NORTH:
        return 1;
    case WEST:
        return 2;
    case SOUTH:
        return 3;
    default:
        return -1;
    }
}

bool is_cardinal_dir(Direction dir)
{
    return dir == EAST || dir == NORTH || dir == WEST || dir == SOUTH;
}
