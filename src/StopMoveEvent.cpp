#include "StopMoveEvent.hpp"

/**
 * Creates a new MoveEvent in the given direction.
 *
 * @param dir The direction this move event is pointing towards
 */
StopMoveEvent::StopMoveEvent(Direction dir)
{
    this->dir = dir;
}

Event::Event_Type StopMoveEvent::get_type()
{
    return END_UNIT_MOVE;
}
