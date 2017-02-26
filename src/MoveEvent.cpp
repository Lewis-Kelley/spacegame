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

Event::Event_Type MoveEvent::get_type()
{
    Event_Type type = Event::NONE;
    switch (dir) {
    case EAST:
        type = Event::START_MOVE_EAST;
        break;
    case NORTH:
        type = Event::START_MOVE_NORTH;
        break;
    case WEST:
        type = Event::START_MOVE_WEST;
        break;
    case SOUTH:
        type = Event::START_MOVE_SOUTH;
        break;
    case NO_DIRECTION:
        type = Event::NONE;
        break;
    }

    return type;
}
