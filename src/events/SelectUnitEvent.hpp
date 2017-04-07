#ifndef SELECTUNITEVENT_H
#define SELECTUNITEVENT_H

#include "../entities/Unit.hpp"
#include "Event.hpp"

/**
 * Event signalling that a Unit has been selected.
 */
class SelectUnitEvent : public Event {
 private:
    Unit *selected;

 public:
    SelectUnitEvent() { }

    /**
     * Initialize a new SselectUnitEvent with the given Unit as the
     * one that has been selected.
     *
     * @param selected The Unit that has been selected.
     */
    explicit SelectUnitEvent(Unit *selected) : selected(selected) { }

    /**
     * @return The Unit that was selected.
     */
    Unit *get_selected() { return selected; }
};

#endif /* SELECTUNITEVENT_H */
