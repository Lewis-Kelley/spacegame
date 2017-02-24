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
    return (Direction)(((int)dir + 2) % 4);
}
