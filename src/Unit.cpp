#include "Unit.hpp"

/**
 * Create a new Unit at the passed Tile.
 *
 * @param tile The Tile this Unit will be located at.
 */
Unit::Unit(Tile *tile) : Entity(tile), team_name("None") { }

/**
 * Create a new Unit with the given image.
 *
 * @param tile The Tile this Unit occupies.
 * @param img The Sprite that represents this Unit.
 */
Unit::Unit(Tile *tile, TileDrawable *img) : Entity(tile, img), team_name("None")
{ }

bool Unit::stops_ent(Entity *other)
{
    return other->is_unit() && ((Unit *)other)->get_team_name() != team_name;
}
