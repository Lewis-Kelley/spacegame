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
    if (dir == NO_DIRECTION) {
        return NO_DIRECTION;
    }

    int shifted = (int)dir << 2;
    shifted = (shifted & 0xc) + (shifted >> 4);
    return (Direction)shifted;
    // return (Direction)(((int)dir + 2) % 4);
}

void print_dir(Direction dir)
{
    switch (dir) {
    case NO_DIRECTION:
        printf("NO_DIRECTION\n");
        break;
    case EAST:
        printf("EAST\n");
        break;
    case NORTH:
        printf("NORTH\n");
        break;
    case WEST:
        printf("WEST\n");
        break;
    case SOUTH:
        printf("SOUTH\n");
        break;
    default:
        printf("Diagonal\n");
        break;
    }
}
