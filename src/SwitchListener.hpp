#ifndef SWITCHLISTENER_H
#define SWITCHLISTENER_H

#include <queue>

#include "Unit.hpp"
#include "Listener.hpp"
#include "Events.hpp"
#include "SwitchEvent.hpp"

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
