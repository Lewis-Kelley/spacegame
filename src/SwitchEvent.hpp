#ifndef SWITCHEVENT_H
#define SWITCHEVENT_H

#include "Entity.hpp"
#include "Event.hpp"

/**
 * Toggles which Unit is currently selected.
 */
class SwitchEvent : public Event {
private:
    Unit *from;
    Unit *to;
public:
    /**
     * Initializes a new SwitchEvent with the given Unit's to switch.
     *
     * @param from The Unit that is losing control.
     * @param to The Unit that is gaining control.
     */
    SwitchEvent(Unit *from, Unit *to) : from(from), to(to) { }
    Event_Type get_type() { return Event::SWITCH_UNITS; }

    /**
     * @return The Unit that is losing control.
     */
    Entity *get_from() { return from; }

    /**
     * @return The Unit that is gaining control.
     */
    Entity *get_to() { return to; }
};

#endif /* SWITCHEVENT_H */
