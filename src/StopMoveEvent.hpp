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

    /**
     * @return The direction this StopMoveEvent corresponds to.
     */
    Direction get_direction() { return dir; }
};

#endif /* STOPMOVEEVENT_H */
