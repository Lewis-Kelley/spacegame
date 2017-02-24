#include "Unit.hpp"

/**
 * Create a new Unit at the passed Tile.
 *
 * @param tile The Tile this Unit will be located at.
 */
Unit::Unit(Tile *tile) : Entity(tile)
{
}

/**
 * Create a new Unit with the given image.
 *
 * @param tile The Tile this Unit occupies.
 * @param img The Sprite that represents this Unit.
 */
Unit::Unit(Tile *tile, Drawable *img) : Entity(tile, img) {
}
