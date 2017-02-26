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
    moving = NO_DIRECTION;
}

void Fighter::handle_attack(Attack *att)
{
}

bool Fighter::move_fighter(Direction dir)
{
    TileDrawable *img = (TileDrawable *)Entity::image;

    if (img->is_moving()) {
        return false;
    }

    img->start_move(MOVE_SPEED, 1, dir);

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
        moving = dir;
    }
}

void Fighter::handle_stop_event(StopMoveEvent *event)
{
    if (event->get_direction() == moving) {
        moving = NO_DIRECTION;
    }
}

void Fighter::handle_move_finished_event(MoveFinishedEvent *event)
{
    if (moving == NO_DIRECTION) {
        return;
    }

    move_fighter(moving);
}

void Fighter::catch_event(Event *event)
{
    switch (event->get_type()) {
    case Event::START_MOVE_EAST:
    case Event::START_MOVE_NORTH:
    case Event::START_MOVE_WEST:
    case Event::START_MOVE_SOUTH:
        handle_move_event((MoveEvent *)event);
        break;
    case Event::END_MOVE_EAST:
    case Event::END_MOVE_NORTH:
    case Event::END_MOVE_WEST:
    case Event::END_MOVE_SOUTH:
        handle_stop_event((StopMoveEvent *)event);
        break;
    case Event::MOVE_FINISHED:
        handle_move_finished_event((MoveFinishedEvent *)event);
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
