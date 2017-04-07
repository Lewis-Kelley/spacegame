#ifndef QUITEVENT_H
#define QUITEVENT_H

#include "Event.hpp"

/**
 * Event that will quit the game.
 */
class QuitEvent : public Event {
 public:
    virtual ~QuitEvent() { }
};

#endif /* QUITEVENT_H */
