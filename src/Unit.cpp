#include "Unit.hpp"

Unit::Unit() : Entity()
{
}

/**
 * Create a new Unit with the given image.
 *
 * @param img The Drawable that represents this Unit.
 */
Unit::Unit(Drawable *img) : Entity(img) {
}
