#include "SwitchListener.hpp"

/**
 * Creates a new SwitchListener with a reference to some std::queue of
 * Unit's to use.
 */
SwitchListener::SwitchListener(std::queue<Unit *> *units) : units(units)
{
    event_handler::add_listener(Event::TRIGGER_SWITCH, this);
}

void SwitchListener::catch_event(Event *event)
{
    if (event->get_type() != Event::TRIGGER_SWITCH) {
        return;
    }

    Unit *temp = units->front();

    if (!temp->can_stop()) {
        return;
    }

    units->pop();
    units->push(temp);
    events::event_queue.push(new DeselectUnitEvent(temp));
    events::event_queue.push(new SelectUnitEvent(units->front()));
}