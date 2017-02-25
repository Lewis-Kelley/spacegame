#include "Fighter.hpp"

/**
 * Constructs a new Fighter by calling the Unit's constructor.
 *
 * @param tile The Tile this Fighter occupies.
 * @param img The image representing this Fighter.
 */
Fighter::Fighter(Tile *tile, Drawable *img)
    : Unit(tile, new TileDrawable(50, img)) { }

void Fighter::handle_attack(Attack *att)
{
}

/**
 * Handles a given MoveEvent, starting an animation to move the ship
 * and updating which Tile the Fighter currently occupies.
 *
 * @param event The MoveEvent to handle
 */
void Fighter::handle_move_event(MoveEvent *event) {
    Direction dir;
    double speed = 0.1;
    switch(event->get_type()) {
    case Event::START_MOVE_EAST:
        dir = EAST;
        break;
    case Event::START_MOVE_NORTH:
        dir = NORTH;
        break;
    case Event::START_MOVE_WEST:
        dir = WEST;
        break;
    case Event::START_MOVE_SOUTH:
        dir = SOUTH;
        break;
    default:
        fprintf(stderr,
                "Invalid MoveEvent received in Fighter::handle_move_event.\n");
        return;
    }

    TileDrawable *img = (TileDrawable *)Entity::image;
    try {
        img->start_move(speed, 1, dir);
    } catch (std::exception e) {
        fprintf(stderr, "%s\n", e.what());
        return;
    }

    if (!move_ent(dir)) {
        img->stop_move();
        return;
    }

    occ_tile = occ_tile->get_neighbor(dir);
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
