#include "DrawableDecorator.hpp"
void DrawableDecorator::start_move(double dx, double dy, MovementType type)
{
    inner->start_move(dx, dy, type);
}

void DrawableDecorator::start_move(Movement *movement, MovementType type)
{
    inner->start_move(movement, type);
}
