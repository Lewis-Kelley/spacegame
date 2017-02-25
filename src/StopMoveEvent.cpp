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
    Event_Type type = Event::NONE;
    switch (dir) {
    case EAST:
        type = Event::END_MOVE_EAST;
        break;
    case NORTH:
        type = Event::END_MOVE_NORTH;
        break;
    case WEST:
        type = Event::END_MOVE_WEST;
        break;
    case SOUTH:
        type = Event::END_MOVE_SOUTH;
        break;
    }

    return type;
}
