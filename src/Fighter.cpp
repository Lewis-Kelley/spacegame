#include "Fighter.hpp"

/**
 * Constructs a new Fighter by calling the Unit's constructor.
 *
 * @param tile The Tile this Fighter occupies.
 * @param img The image representing this Fighter.
 */
Fighter::Fighter(Tile *tile, Sprite *img) : Unit(tile, img)
{
}

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
    double dx;
    double dy;
    double speed = 0.1;
    switch(event->get_type()) {
    case Event::START_MOVE_EAST:
        dir = EAST;
        dx = speed;
        dy = 0;
        break;
    case Event::START_MOVE_NORTH:
        dir = NORTH;
        dx = 0;
        dy = -speed;
        break;
    case Event::START_MOVE_WEST:
        dir = WEST;
        dx = -speed;
        dy = 0;
        break;
    case Event::START_MOVE_SOUTH:
        dir = SOUTH;
        dx = 0;
        dy = speed;
        break;
    default:
        fprintf(stderr,
                "Invalid MoveEvent received in Fighter::handle_move_event.\n");
        return;
    }

    if (!Entity::move(dir)) {
        return;
    }

    Sprite *sprite = (Sprite *)Entity::image;
    sprite->set_dx(dx);
    sprite->set_dy(dy);
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
