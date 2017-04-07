#include "MovementListener.hpp"

MovementListener::MovementListener()
    : start_listener(this), stop_listener(this), finished_listener(this),
      select_unit_listener(this), deselect_unit_listener(this), controlled(NULL)
{
    auto handler = EventHandler::get_instance();

    MoveEvent move_event;
    StopMoveEvent stop_event;
    MoveFinishedEvent finished_event;
    SelectUnitEvent select_event;
    DeselectUnitEvent deselect_event;

    handler->add_listener(&move_event, &start_listener);
    handler->add_listener(&stop_event, &stop_listener);
    handler->add_listener(&finished_event, &finished_listener);
    handler->add_listener(&select_event, &select_unit_listener);
    handler->add_listener(&deselect_event, &deselect_unit_listener);
}

void MovementListener::StartMoveListener::catch_event(Event *event)
{
    auto move_event = dynamic_cast<MoveEvent *>(event);
    Direction dir = move_event->get_direction();

    if (outer->controlled != NULL && outer->controlled->move_unit(dir)) {
        outer->move_dir = dir;
    } else {
        outer->queue_dir = dir;
    }
}

void MovementListener::StopMoveListener::catch_event(Event *event)
{
    auto stop_event = dynamic_cast<StopMoveEvent *>(event);
    if (stop_event->get_direction() == outer->queue_dir) {
        outer->queue_dir = NO_DIRECTION;
    }

    if (stop_event->get_direction() == outer->move_dir) {
        outer->move_dir = outer->queue_dir;
    }
}

void MovementListener::MoveFinishedListener::catch_event(Event *)
{
    if (outer->move_dir == NO_DIRECTION) {
        if (outer->queue_dir == NO_DIRECTION) {
            return;
        }

        outer->move_dir = outer->queue_dir;
    }

    if (outer->controlled != NULL) {
        outer->controlled->move_unit(outer->move_dir);
    }
}

void MovementListener::SelectUnitListener::catch_event(Event *event)
{
    auto selected_event = dynamic_cast<SelectUnitEvent *>(event);
    outer->controlled = selected_event->get_selected();
}

void MovementListener::DeselectUnitListener::catch_event(Event *)
{
    outer->controlled = NULL;
}
