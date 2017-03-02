#include "Drawable.hpp"

/**
 * Move this image's location by the given delta's.
 *
 * @param dx The shift in the x direction. Positive = right
 * @param dy The shift in the y direction. Positive = down
 */
void Drawable::move(double dx, double dy)
{
    set_draw_x(get_draw_x() + dx);
    set_draw_y(get_draw_y() + dy);
}

/**
 * Move this image's location by the given Movement.
 *
 * @param movement The one-time Movement to perform.
 */
void Drawable::move(Movement movement)
{
    move(movement.dx, movement.dy);
}

/**
 * Start a consistent move for this Drawable.
 *
 * @param dx The amount to move in the x direction per tick.
 * @param dy The amount to move in the y direction per tick.
 * @param type The MovementType of this Movement.
 */
void Drawable::start_move(double dx, double dy, MovementType type)
{
    if (movements.find(type) == movements.end()) {
        movements.insert(movement_pair(type, new Movement(dx, dy)));
    } else {
        movements.at(type)->dx = dx;
        movements.at(type)->dy = dy;
    }
}

/**
 * Start a consistent move for this Drawable.
 *
 * @param movement The Movement detailing how to move each tick.
 * @param type The MovementType of this Movement.
 */
void Drawable::start_move(Movement *movement, MovementType type)
{
    movements.insert(movement_pair(type, movement));
}

/**
 * Stop the Movement with the associated type.
 *
 * @param type The type of Movement to kill.
 */
void Drawable::end_move(MovementType type)
{
    movements.erase(type);
}

void Drawable::update(double delta)
{
    for (std::map<MovementType, Movement *>::iterator iter = movements.begin();
         iter != movements.end(); iter++) {
        move(iter->second->dx * delta, iter->second->dy * delta);
    }
}
