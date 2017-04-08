#ifndef MOVEMENTLISTENER_H
#define MOVEMENTLISTENER_H

#include "../events/EventHandler.hpp"
#include "../entities/Unit.hpp"
#include "../events/MoveEvent.hpp"
#include "../events/StopMoveEvent.hpp"
#include "../events/MoveFinishedEvent.hpp"
#include "../events/SelectUnitEvent.hpp"
#include "../events/DeselectUnitEvent.hpp"

/**
 * Listenes for movement Event's, keeps track of the selected Unit,
 * and moves the Unit as necessary.
 */
class MovementListener {
 private:
    Unit *controlled;
    Direction move_dir;
    Direction queue_dir;

 public:
    MovementListener();
    void handle_start_move(Event *);
    void handle_stop_move(Event *);
    void handle_finished_move(Event *);
    void handle_select_unit(Event *);
    void handle_deselect_unit(Event *);
};

#endif /* MOVEMENTLISTENER_H */
