#include "SwitchListener.hpp"

/**
 * Creates a new SwitchListener with a reference to some std::queue of
 * Unit's to use.
 */
SwitchListener::SwitchListener(std::queue<Unit *> *units) : units(units) { }

void SwitchListener::catch_event(Event *event)
{
    if (event->get_type() == Event::TRIGGER_SWITCH) {
        Unit *temp = units->front();
        units->pop();
        units->push(temp);
        events::event_queue.push(new DeselectUnitEvent(temp));
        events::event_queue.push(new SelectUnitEvent(units->front()));
    }
}
