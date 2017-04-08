#include "SwitchListener.hpp"

/**
 * Creates a new SwitchListener with a reference to some std::queue of
 * Unit's to use.
 */
SwitchListener::SwitchListener(std::queue<Unit *> *units) : units(units)
{
    auto handler = EventHandler::get_instance();

    TriggerSwitchEvent switch_event;
    handler->add_listener(&switch_event, [this](Event *event)
                          { handle_switch(event); });
}

void SwitchListener::handle_switch(Event *)
{
    Unit *temp = units->front();

    if (!temp->can_stop()) {
        return;
    }

    units->pop();
    units->push(temp);
    events::event_queue.push(new DeselectUnitEvent(temp));
    events::event_queue.push(new SelectUnitEvent(units->front()));
}
