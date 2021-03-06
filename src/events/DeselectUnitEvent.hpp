#ifndef DESELECTUNITEVENT_H
#define DESELECTUNITEVENT_H

#include "../entities/Unit.hpp"
#include "Event.hpp"

/**
 * Event signalling that a Unit has been deselected.
 */
class DeselectUnitEvent : public Event {
 private:
    Unit *deselected;

 public:
    DeselectUnitEvent() { }

    /**
     * Initialize a new DeselectUnitEvent with the given Unit as the
     * one that has been deselected.
     *
     * @param deselected The Unit that has been deselected.
     */
    explicit DeselectUnitEvent(Unit *deselected) : deselected(deselected) { }

    /**
     * @return The Unit that was deselected.
     */
    Unit *get_deselected() { return deselected; }
};

#endif /* DESELECTUNITEVENT_H */
