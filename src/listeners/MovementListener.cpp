#include "MovementListener.hpp"

MovementListener::MovementListener() : controlled(NULL)
{
    auto handler = EventHandler::get_instance();

    MoveEvent move_event;
    StopMoveEvent stop_event;
    MoveFinishedEvent finished_event;
    SelectUnitEvent select_event;
    DeselectUnitEvent deselect_event;

    handler->add_listener(&move_event, [this](Event *event)
                          { handle_start_move(event); });
    handler->add_listener(&stop_event, [this](Event *event)
                          { handle_stop_move(event); });
    handler->add_listener(&finished_event, [this](Event *event)
                          { handle_finished_move(event); });
    handler->add_listener(&select_event, [this](Event *event)
                          { handle_select_unit(event); });
    handler->add_listener(&deselect_event, [this](Event *event)
                          { handle_deselect_unit(event); });
}

void MovementListener::handle_start_move(Event *event)
{
    auto move_event = dynamic_cast<MoveEvent *>(event);
    Direction dir = move_event->get_direction();

    if (controlled != NULL && controlled->move_unit(dir)) {
        move_dir = dir;
    } else {
        queue_dir = dir;
    }
}

void MovementListener::handle_stop_move(Event *event)
{
    auto stop_event = dynamic_cast<StopMoveEvent *>(event);
    if (stop_event->get_direction() == queue_dir) {
        queue_dir = NO_DIRECTION;
    }

    if (stop_event->get_direction() == move_dir) {
        move_dir = queue_dir;
    }
}

void MovementListener::handle_finished_move(Event *)
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

void MovementListener::handle_select_unit(Event *event)
{
    auto selected_event = dynamic_cast<SelectUnitEvent *>(event);
    controlled = selected_event->get_selected();
}

void MovementListener::handle_deselect_unit(Event *)
{
    controlled = NULL;
}
