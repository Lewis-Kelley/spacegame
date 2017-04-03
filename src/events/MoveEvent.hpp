#ifndef MOVEEVENT_H
#define MOVEEVENT_H

#include <stdio.h>

#include "Event.hpp"
#include "../util/Direction.hpp"

/**
 * Event dealing with moving units.
 */
class MoveEvent : public Event {
 private:
    Direction dir;

 public:
    explicit MoveEvent(Direction dir);
    virtual Event_Type get_type();

    /**
     * @return The direction this MoveEvent corresponds to.
     */
    Direction get_direction() { return dir; }
};

#endif /* MOVEEVENT_H */
