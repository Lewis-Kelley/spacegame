#ifndef MOVEFINISHEDEVENT_H
#define MOVEFINISHEDEVENT_H

#include "Event.hpp"

/**
 * Event dealing with the animation of a movement ending.
 */
class MoveFinishedEvent : public Event {
 public:
    virtual Event_Type get_type() { return UNIT_MOVE_FINISHED; }
};

#endif /* MOVEFINISHEDEVENT_H */
