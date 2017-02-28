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
 * Start a consistent move for this Drawable.
 *
 * @param dx The amount to move in the x direction per tick.
 * @param dy The amount to move in the y direction per tick.
 */
void Drawable::start_move(double dx, double dy)
{
    this->dx = dx;
    this->dy = dy;
}

void Drawable::update(double delta)
{
    move(dx * delta, dy * delta);
}
