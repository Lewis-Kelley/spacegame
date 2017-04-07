#ifndef STOPMOVEEVENT_H
#define STOPMOVEEVENT_H

#include <stdio.h>

#include "Event.hpp"
#include "../util/Direction.hpp"

/**
 * Event dealing with moving units.
 */
class StopMoveEvent : public Event {
 private:
    Direction dir;

 public:
    StopMoveEvent() { }
    explicit StopMoveEvent(Direction dir);

    /**
     * @return The direction this StopMoveEvent corresponds to.
     */
    Direction get_direction() { return dir; }
};

#endif /* STOPMOVEEVENT_H */
