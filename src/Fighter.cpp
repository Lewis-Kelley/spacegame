#include "Fighter.hpp"

/**
 * Constructs a new Fighter by calling the Unit's constructor.
 *
 * @param tile The Tile this Fighter occupies.
 * @param img The image representing this Fighter.
 */
Fighter::Fighter(Tile *tile, Drawable *img)
    : Unit(tile, new TileDrawable(50, img))
{
    moving_dir = NO_DIRECTION;
    camera_dir = NO_DIRECTION;
}

void Fighter::handle_attack(Attack *att)
{
}

/**
 * Attempts to move this Fighter in the given Direction.
 *
 * @param dir The Direction in which to move this Fighter.
 * @return True if successful, false if there was a problem.
 */
bool Fighter::move_fighter(Direction dir)
{
    TileDrawable *img = (TileDrawable *)Entity::image;

    if (img->is_moving()) {
        return false;
    }

    img->start_tile_move(MOVE_SPEED, 1, dir);

    if (!move_ent(dir)) {
        img->kill_move();
        return false;
    }

    occ_tile = occ_tile->get_neighbor(dir);
    return true;
}

/**
 * Handles a given MoveEvent, starting an animation to move the ship
 * and updating which Tile the Fighter currently occupies.
 *
 * @param event The MoveEvent to handle
 */
void Fighter::handle_move_event(MoveEvent *event)
{
    Direction dir = event->get_direction();

    if (move_fighter(dir)) {
        moving_dir = dir;
    }
}

/**
 * Handle a StopMoveEvent to stop the Fighter from continuing to move.
 *
 * @param event The StopMoveEvent to handle.
 */
void Fighter::handle_stop_event(StopMoveEvent *event)
{
    if (event->get_direction() == moving_dir) {
        moving_dir = NO_DIRECTION;
    }
}

/**
 * Handle a MoveFinishedEvent to continue moving in whatever direction
 * the Fighter is currently moving_dir.
 *
 * @param event The MoveFinishedEvent to handle.
 */
void Fighter::handle_move_finished_event(MoveFinishedEvent *event)
{
    if (moving_dir == NO_DIRECTION) {
        return;
    }

    move_fighter(moving_dir);
}

/**
 * Handle a CameraMoveEvent by passing it through to the underlying
 * Drawable image.
 *
 * @param event The CameraMoveEvent to handle.
 */
void Fighter::handle_camera_move_event(CameraMoveEvent *event)
{
    image->start_move(event->get_dx(), event->get_dy(), CAMERA);
    camera_dir = event->get_dir();
}

/**
 * Handle a StopCameraMoveEvent by halting the underlying Drawable
 * motion.
 *
 * @param event The StopCameraMoveEvent to handle.
 */
void Fighter::handle_camera_stop_move_event(StopCameraMoveEvent *event)
{
    if (event->get_dir() == camera_dir) {
        image->end_move(CAMERA);
        camera_dir = NO_DIRECTION;
    }
}

void Fighter::handle_switch_units_event(SwitchEvent *event)
{
    EventHandler *handler = EventHandler::get_instance();

    if (event->get_from() == this) {
        handler->remove_listener(Event::START_UNIT_MOVE, this);
        handler->remove_listener(Event::END_UNIT_MOVE, this);
        handler->remove_listener(Event::UNIT_MOVE_FINISHED, this);
    }

    if (event->get_to() == this) {
        handler->add_listener(Event::START_UNIT_MOVE, this);
        handler->add_listener(Event::END_UNIT_MOVE, this);
        handler->add_listener(Event::UNIT_MOVE_FINISHED, this);
    }
}

void Fighter::catch_event(Event *event)
{
    switch (event->get_type()) {
    case Event::START_UNIT_MOVE:
        handle_move_event((MoveEvent *)event);
        break;
    case Event::END_UNIT_MOVE:
        handle_stop_event((StopMoveEvent *)event);
        break;
    case Event::UNIT_MOVE_FINISHED:
        handle_move_finished_event((MoveFinishedEvent *)event);
        break;
    case Event::START_CAMERA_MOVE:
        handle_camera_move_event((CameraMoveEvent *)event);
        break;
    case Event::STOP_CAMERA_MOVE:
        handle_camera_stop_move_event((StopCameraMoveEvent *)event);
        break;
    case Event::SWITCH_UNITS:
        handle_switch_units_event((SwitchEvent *)event);
        break;
    default:
        break;
    }
}

Attack *Fighter::make_attack(Unit *target)
{
    return NULL;
}

short Fighter::get_move_range()
{
    return 0;
}
