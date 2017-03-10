#ifndef TRIGGERSWITCHEVENT_H
#define TRIGGERSWITCHEVENT_H

#include "Event.hpp"

/**
 * Signals for a switch in which Unit is currently selected, but
 * doesn't contain the Unit's that will be affected.
 */
class TriggerSwitchEvent : public Event {
    Event_Type get_type() { return Event::TRIGGER_SWITCH; }
};

#endif /* TRIGGERSWITCHEVENT_H */
