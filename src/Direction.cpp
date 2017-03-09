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

bool has_direction(Direction checked_dir, Direction goal_dir)
{
    return (checked_dir & goal_dir) == goal_dir;
}

bool is_cardinal_dir(Direction dir)
{
    return dir == EAST || dir == NORTH || dir == WEST || dir == SOUTH;
}

/**
 * Check if the passed direction is a horizontal (EAST/WEST)
 * Direction.
 *
 * @param dir The Direction to check.
 * @return True if the direction is horizontal, false if
 * diagonal or vertical
 */
bool is_horiz_dir(Direction dir)
{
    return dir == EAST || dir == WEST;
}

/**
 * Return the result of merging the two directions, which may include
 * cancellations.
 *
 * @param dirA The first Direction to merge.
 * @param dirB The second Direction to merge.
 * @return A new Direction that merges the two passsed Direction's.
 */
Direction merge_directions(Direction dirA, Direction dirB)
{
    Direction res = NO_DIRECTION;

    for (Direction i = EAST; i <= SOUTH; i = (Direction)(i << 1)) {
        if ((dirA & i) != 0 && (dirB & opp_dir(i)) != 0) {
            res = (Direction)(res + i);
        }
    }

    return res;
}

Direction remove_direction(Direction base_dir, Direction dir_to_rem)
{
    return (Direction)(base_dir & ~dir_to_rem);
}
