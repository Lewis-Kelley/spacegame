#ifndef SELECTUNITEVENT_H
#define SELECTUNITEVENT_H

#include "Unit.hpp"
#include "Event.hpp"

/**
 * Event signalling that a Unit has been selected.
 */
class SelectUnitEvent : public Event {
private:
    Unit *selected;
public:
    /**
     * Initialize a new SselectUnitEvent with the given Unit as the
     * one that has been selected.
     *
     * @param selected The Unit that has been selected.
     */
    SelectUnitEvent(Unit *selected) : selected(selected) { }
    Event_Type get_type() { return SELECT_UNIT; }

    /**
     * @return The Unit that was selected.
     */
    Unit *get_selected() { return selected; }
};

#endif /* SELECTUNITEVENT_H */
