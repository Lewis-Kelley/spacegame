#include "MoveEvent.hpp"

/**
 * Creates a new MoveEvent in the given direction.
 *
 * @param dir The direction this move event is pointing towards
 */
MoveEvent::MoveEvent(Direction dir)
{
    this->dir = dir;
}
