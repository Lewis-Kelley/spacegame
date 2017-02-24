#ifndef QUITEVENT_H
#define QUITEVENT_H

#include "Event.hpp"

class QuitEvent : public Event {
public:
    virtual ~QuitEvent() { }
    virtual Event_Type get_type()
    {
        return Event::QUIT;
    }
};

#endif /* QUITEVENT_H */
