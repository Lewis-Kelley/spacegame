#include "Fighter.hpp"

void Fighter::init()
{
    event_handler::add_listener(Event::START_CAMERA_MOVE, this);
    event_handler::add_listener(Event::STOP_CAMERA_MOVE, this);
    event_handler::add_listener(Event::SELECT_UNIT, this);
    event_handler::add_listener(Event::DESELECT_UNIT, this);
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

void Fighter::catch_event(Event *event)
{
    switch (event->get_type()) {
    case Event::START_CAMERA_MOVE:
        handle_camera_move_event((CameraMoveEvent *)event);
        break;
    case Event::STOP_CAMERA_MOVE:
        handle_camera_stop_move_event((StopCameraMoveEvent *)event);
        break;
    default:
        break;
    }
}

Attack *Fighter::make_attack(Unit *target)
{
    // TODO Implement
    return NULL;
}

short Fighter::get_move_range()
{
    // TODO Replace with some proportional value.
    return 4;
}

std::pair<short, short> Fighter::get_attack_range()
{
    // TODO Replace with some proportional value.
    std::pair<short, short> pair(1, 2);
    return pair;
}
