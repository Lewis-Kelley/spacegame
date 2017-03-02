#include "Fighter.hpp"

void Fighter::init()
{
    EventHandler *handler = EventHandler::get_instance();
    handler->add_listener(Event::START_CAMERA_MOVE, this);
    handler->add_listener(Event::STOP_CAMERA_MOVE, this);
    handler->add_listener(Event::SELECT_UNIT, this);
    handler->add_listener(Event::DESELECT_UNIT, this);
    moving_dir = NO_DIRECTION;
    camera_dir = NO_DIRECTION;
    queued_dir = NO_DIRECTION;
}

/**
 * Instantiate a new Fighter at the given location with the given image.
 *
 * @param tilemap A reference to a TileMap that will be used to access
 * the Tile this Fighter will occupy.
 * @param row The row this Fighter will occupy.
 * @param col The column this Fighter will occupy.
 * @param img The TileDrawable that will be used to draw this Fighter.
 */
Fighter::Fighter(TileMap *tilemap, short row, short col, TileDrawable *img)
    : Unit(tilemap, row, col, img)
{
    init();
}

/**
 * Instantiate a new Fighter at the given location with the given image.
 *
 * @param tile_width The width of a Tile in pixels.
 * @param tilemap A reference to a TileMap that will be used to access
 * the Tile this Fighter will occupy.
 * @param row The row this Fighter will occupy.
 * @param col The column this Fighter will occupy.
 * @param img The Drawable that will be used to draw this Fighter. This will
 * be wrapped in a new TileDrawable object.
 */
Fighter::Fighter(double tile_width, TileMap *tilemap, short row, short col,
                 Drawable *img) : Unit(tile_width, tilemap, row, col, img)
{
    init();
}

/**
 * Constructs a new Fighter by calling the Unit's constructor.
 *
 * @param tile The Tile this Fighter occupies.
 * @param img The image representing this Fighter.
 */
Fighter::Fighter(Tile *tile, TileDrawable *img) : Unit(tile, img)
{
    init();
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
    if (image->is_moving()) {
        return false;
    }

    image->start_tile_move(MOVE_SPEED, 1, dir);

    if (!move_ent(dir)) {
        image->kill_move();
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
    } else {
        queued_dir = dir;
    }
}

/**
 * Handle a StopMoveEvent to stop the Fighter from continuing to move.
 *
 * @param event The StopMoveEvent to handle.
 */
void Fighter::handle_stop_event(StopMoveEvent *event)
{
    if (event->get_direction() == queued_dir) {
        queued_dir = NO_DIRECTION;
    }

    if (event->get_direction() == moving_dir) {
        moving_dir = queued_dir;
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
        if (queued_dir == NO_DIRECTION) {
            return;
        }

        moving_dir = queued_dir;
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
    Direction event_dir = event->get_dir();
    MovementType type = (event_dir & (EAST | WEST)) != 0
        ? CAMERA_X : CAMERA_Y;
    if (camera_dir == NO_DIRECTION
        || (is_cardinal_dir(camera_dir) && event_dir != opp_dir(camera_dir))) {
        camera_dir = (Direction)(camera_dir | event_dir);
        image->start_move(event->get_dx(), event->get_dy(), type);
    }
}

/**
 * Handle a StopCameraMoveEvent by halting the underlying Drawable
 * motion.
 *
 * @param event The StopCameraMoveEvent to handle.
 */
void Fighter::handle_camera_stop_move_event(StopCameraMoveEvent *event)
{
    if ((event->get_dir() | camera_dir) == 0) {
        return;
    }

    MovementType type = (event->get_dir() & (EAST | WEST)) != 0
        ? CAMERA_X : CAMERA_Y;

    image->end_move(type);
    camera_dir = (Direction)(camera_dir & ~event->get_dir());
}

void Fighter::handle_select_unit_event(SelectUnitEvent *event)
{
    EventHandler *handler = EventHandler::get_instance();

    if (event->get_selected() == this) {
        handler->add_listener(Event::START_UNIT_MOVE, this);
        handler->add_listener(Event::END_UNIT_MOVE, this);
        handler->add_listener(Event::UNIT_MOVE_FINISHED, this);
    }
}

void Fighter::handle_deselect_unit_event(DeselectUnitEvent *event)
{
    EventHandler *handler = EventHandler::get_instance();

    if (event->get_deselected() == this) {
        handler->remove_listener(Event::START_UNIT_MOVE, this);
        handler->remove_listener(Event::END_UNIT_MOVE, this);
        handler->remove_listener(Event::UNIT_MOVE_FINISHED, this);
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

Attack *Fighter::make_attack(Unit *target)
{
    return NULL;
}

short Fighter::get_move_range()
{
    return 4;
}
