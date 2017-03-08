#ifndef MOVEMENTLISTENER_H
#define MOVEMENTLISTENER_H

#include "EventHandler.hpp"
#include "Unit.hpp"
#include "Listener.hpp"
#include "MoveEvent.hpp"
#include "StopMoveEvent.hpp"
#include "MoveFinishedEvent.hpp"
#include "SelectUnitEvent.hpp"
#include "DeselectUnitEvent.hpp"

/**
 * Listenes for movement Event's, keeps track of the selected Unit,
 * and moves the Unit as necessary.
 */
class MovementListener : public Listener {
private:
    Unit *controlled;
    Direction move_dir;
    Direction queue_dir;

    void handle_start_unit_move_event(MoveEvent *event);
    void handle_stop_move_event(StopMoveEvent *event);
    void handle_move_finished_event(MoveFinishedEvent *event);
    void handle_select_unit_event(SelectUnitEvent *event);
    void handle_deselect_unit_event(DeselectUnitEvent *event);
public:
    MovementListener();
    void catch_event(Event *event);
};

#endif /* MOVEMENTLISTENER_H */