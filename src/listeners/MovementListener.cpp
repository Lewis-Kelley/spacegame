#include "MovementListener.hpp"

MovementListener::MovementListener() : controlled(NULL)
{
    auto handler = EventHandler::get_instance();

    handler->add_listener(Event::START_UNIT_MOVE, this);
    handler->add_listener(Event::END_UNIT_MOVE, this);
    handler->add_listener(Event::UNIT_MOVE_FINISHED, this);
    handler->add_listener(Event::SELECT_UNIT, this);
    handler->add_listener(Event::DESELECT_UNIT, this);
}

void MovementListener::catch_event(Event *event)
{
    switch (event->get_type()) {
    case Event::START_UNIT_MOVE:
        handle_start_unit_move_event((MoveEvent *)event);
        break;
    case Event::END_UNIT_MOVE:
        handle_stop_move_event((StopMoveEvent *)event);
        break;
    case Event::UNIT_MOVE_FINISHED:
        handle_move_finished_event((MoveFinishedEvent *)event);
        break;
    case Event::SELECT_UNIT:
        handle_select_unit_event((SelectUnitEvent *)event);
        break;
    case Event::DESELECT_UNIT:
        handle_deselect_unit_event((DeselectUnitEvent *)event);
        break;
    default:
        break;
    }
}

void MovementListener::handle_start_unit_move_event(MoveEvent *event)
{
    Direction dir = event->get_direction();

    if (controlled != NULL && controlled->move_unit(dir)) {
        move_dir = dir;
    } else {
        queue_dir = dir;
    }
}

void MovementListener::handle_stop_move_event(StopMoveEvent *event)
{
    if (event->get_direction() == queue_dir) {
        queue_dir = NO_DIRECTION;
    }

    if (event->get_direction() == move_dir) {
        move_dir = queue_dir;
    }
}

void MovementListener::handle_move_finished_event(MoveFinishedEvent *event)
{
    if (move_dir == NO_DIRECTION) {
        if (queue_dir == NO_DIRECTION) {
            return;
        }

        move_dir = queue_dir;
    }

    if (controlled != NULL) {
        controlled->move_unit(move_dir);
    }
}

void MovementListener::handle_select_unit_event(SelectUnitEvent *event)
{
    controlled = event->get_selected();
}

void MovementListener::handle_deselect_unit_event(DeselectUnitEvent *event)
{
    controlled = NULL;
}
