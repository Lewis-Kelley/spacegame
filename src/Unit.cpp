#include "Unit.hpp"

/**
 * Instantiate a new Unit at the given location without any image.
 *
 * @param tilemap A reference to a TileMap that will be used to access
 * the Tile this Unit will occupy.
 * @param row The row this Unit will occupy.
 * @param col The column this Unit will occupy.
 */
Unit::Unit(TileMap *tilemap, short row, short col)
    : Entity(tilemap->at(row, col)) { }

/**
 * Instantiate a new Unit at the given location with the given image.
 *
 * @param tilemap A reference to a TileMap that will be used to access
 * the Tile this Unit will occupy.
 * @param row The row this Unit will occupy.
 * @param col The column this Unit will occupy.
 * @param img The TileDrawable that will be used to draw this Unit.
 */
Unit::Unit(TileMap *tilemap, short row, short col, TileDrawable *img)
    : Entity(tilemap->at(row, col), img) { }

/**
 * Instantiate a new Unit at the given location with the given image.
 *
 * @param tile_width The width of a Tile in pixels.
 * @param tilemap A reference to a TileMap that will be used to access
 * the Tile this Unit will occupy.
 * @param row The row this Unit will occupy.
 * @param col The column this Unit will occupy.
 * @param img The Drawable that will be used to draw this Unit. This will
 * be wrapped in a new TileDrawable object.
 */
Unit::Unit(double tile_width, TileMap *tilemap, short row, short col,
           Drawable *img)
    : Entity(tilemap->at(row, col),
             new TileDrawable(tile_width, img, row, col)) { }

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
