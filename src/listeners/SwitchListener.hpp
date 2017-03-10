#ifndef SWITCHLISTENER_H
#define SWITCHLISTENER_H

#include <queue>

#include "../entities/Unit.hpp"
#include "Listener.hpp"
#include "../events/Events.hpp"
#include "../events/DeselectUnitEvent.hpp"
#include "../events/SelectUnitEvent.hpp"
#include "../events/EventHandler.hpp"

/**
 * Catches a SWITCH Event and switches control to the next Unit.
 */
class SwitchListener : public Listener {
private:
    std::queue<Unit *> *units;
public:
    SwitchListener(std::queue<Unit *> *units);
    void catch_event(Event *event);
};

#endif /* SWITCHLISTENER_H */
