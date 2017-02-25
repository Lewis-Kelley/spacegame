#ifndef STOPMOVEEVENT_H
#define STOPMOVEEVENT_H

#include <stdio.h>

#include "Event.hpp"
#include "Direction.hpp"

/**
 * Event dealing with moving units.
 */
class StopMoveEvent : public Event {
private:
    Direction dir;
public:
    StopMoveEvent(Direction dir);
    virtual Event_Type get_type();
};

#endif /* STOPMOVEEVENT_H */
