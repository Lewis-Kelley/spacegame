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
    switch (dir) {
    case EAST:
        return WEST;
    case NORTH:
        return SOUTH;
    case WEST:
        return EAST;
    case SOUTH:
        return NORTH;
    }

    return (Direction)(((int)dir + 2) % 4);
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
