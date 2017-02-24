#ifndef MOVEEVENT_H
#define MOVEEVENT_H

#include "Event.hpp"
#include "Direction.hpp"

/**
 * Event dealing with moving units.
 */
class MoveEvent : public Event {
private:
    Direction dir;
public:
    MoveEvent(Direction dir);
    virtual Event_Type get_type();
};

#endif /* MOVEEVENT_H */
