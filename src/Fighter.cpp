#include "Fighter.hpp"

/**
 * Constructs a new Fighter by calling the Unit's constructor.
 *
 * @param img The image representing this Fighter.
 */
Fighter::Fighter(Drawable *img) : Unit(img)
{
}

void Fighter::handle_attack(Attack *att)
{
}

/**
 * Take whatever action is appropriate for the given event.
 *
 * @param event The event to handle.
 */
void Fighter::handle_event(SDL_Event *event)
{
}

void Fighter::catch_event(Event *event)
{
}

Attack *Fighter::make_attack(Unit *target)
{
    return NULL;
}

short Fighter::get_move_range()
{
    return 0;
}
