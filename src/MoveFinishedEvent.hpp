#ifndef MOVEFINISHEDEVENT_H
#define MOVEFINISHEDEVENT_H

#include "Event.hpp"

class MoveFinishedEvent : public Event {
public:
    virtual Event_Type get_type() { return MOVE_FINISHED; }
};

#endif /* MOVEFINISHEDEVENT_H */
