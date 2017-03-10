#include "Fighter.hpp"

/**
 * Instantiate a new Fighter at the given location with the given image.
 *
 * @param tilemap A reference to a TileMap that will be used to access
 * the Tile this Fighter will occupy.
 * @param row The row this Fighter will occupy.
 * @param col The column this Fighter will occupy.
 * @param img The TileDrawable that will be used to draw this Fighter.
 */
Fighter::Fighter(TileMap *tilemap, short row, short col, TileDrawable *img)
    : Unit(tilemap, row, col, img) {}

/**
 * Instantiate a new Fighter at the given location with the given image.
 *
 * @param tile_width The width of a Tile in pixels.
 * @param tilemap A reference to a TileMap that will be used to access
 * the Tile this Fighter will occupy.
 * @param row The row this Fighter will occupy.
 * @param col The column this Fighter will occupy.
 * @param img The Drawable that will be used to draw this Fighter. This will
 * be wrapped in a new TileDrawable object.
 */
Fighter::Fighter(double tile_width, TileMap *tilemap, short row, short col,
                 Drawable *img) : Unit(tile_width, tilemap, row, col, img) {}

/**
 * Constructs a new Fighter by calling the Unit's constructor.
 *
 * @param tile The Tile this Fighter occupies.
 * @param img The image representing this Fighter.
 */
Fighter::Fighter(Tile *tile, TileDrawable *img) : Unit(tile, img) {}

void Fighter::handle_attack(Attack *att)
{
    // TODO
}

void Fighter::catch_event(Event *event)
{
    switch (event->get_type()) {
    default:
        break;
    }
}

Attack *Fighter::make_attack(Unit *target)
{
    // TODO Implement
    return NULL;
}

short Fighter::get_move_range()
{
    // TODO Replace with some proportional value.
    return 4;
}

std::pair<short, short> Fighter::get_attack_range()
{
    // TODO Replace with some proportional value.
    std::pair<short, short> pair(1, 2);
    return pair;
}
