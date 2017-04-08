#ifndef SWITCHLISTENER_H
#define SWITCHLISTENER_H

#include <queue>

#include "../entities/Unit.hpp"
#include "../events/Events.hpp"
#include "../events/DeselectUnitEvent.hpp"
#include "../events/SelectUnitEvent.hpp"
#include "../events/EventHandler.hpp"

/**
 * Catches a SWITCH Event and switches control to the next Unit.
 */
class SwitchListener {
 private:
    std::queue<Unit *> *units;

 public:
    explicit SwitchListener(std::queue<Unit *> *units);
    void handle_switch(Event *event);
};

#endif /* SWITCHLISTENER_H */
