#include "TileMap.hpp"

/**
 * Create a new TileMap with the given dimensions and initialize all
 * of the Tiles in it.
 *
 * @param width The width of the requested TileMap
 * @param height The height of the requested TileMap
 */
TileMap::TileMap(short width, short height)
{
    Tile *tile;

    this->width = width;
    this->height = height;
    tiles = new Tile *[width * height]();

    tile = new Tile(0, 0);
    set(tile, 0, 0);
    event_handler::add_listener(Event::SELECT_UNIT, tile);
    event_handler::add_listener(Event::DESELECT_UNIT, tile);

    for (short col = 1; col < width; col++) {
        tile = new Tile(0, col);
        set(tile, 0, col);
        tile->add_neighbor(WEST, at(0, col - 1));
        event_handler::add_listener(Event::SELECT_UNIT, tile);
        event_handler::add_listener(Event::DESELECT_UNIT, tile);
    }

    for (short row = 1; row < height; row++) {
        tile = new Tile(row, 0);
        set(tile, row, 0);
        tile->add_neighbor(NORTH, at(row - 1, 0));
        event_handler::add_listener(Event::SELECT_UNIT, tile);
        event_handler::add_listener(Event::DESELECT_UNIT, tile);

        for (short col = 1; col < width; col++) {
            tile = new Tile(row, col);
            set(tile, row, col);
            tile->add_neighbor(NORTH, at(row - 1, col));
            tile->add_neighbor(WEST, at(row, col - 1));
            event_handler::add_listener(Event::SELECT_UNIT, tile);
            event_handler::add_listener(Event::DESELECT_UNIT, tile);
        }
    }
}

TileMap::~TileMap()
{
    for (short row = 0; row < height; row++) {
        for (short col = 0; col < width; col++) {
            delete at(row, col);
        }
    }

    delete tiles;
}

/**
 * Return the Tile stored at the given coordinates.
 *
 * @param row The row of the requested Tile.
 * @param col The row of the requested Tile.
 * @return The Tile at the given coordinates.
 */
Tile *TileMap::at(short row, short col)
{
    if (in_bounds(row, col)) {
        return tiles[row * width + col];
    }

    OutOfBounds ex;
    throw ex;
}

/**
 * Set the Tile at the given coordinates to the passed tile.
 *
 * @param tile The value to set the Tile to.
 * @param row The row of the requested Tile.
 * @param col The col of the requested Tile.
 */
void TileMap::set(Tile *tile, short row, short col)
{
    if (in_bounds(row, col)) {
        tiles[row * width + col] = tile;
        return;
    }

    OutOfBounds ex;
    throw ex;
}

/**
 * Tests whether the given coordinates are within the bounds of the map.
 *
 * @param row
 * @param col
 * @return True if the coordinates are within bounds, false if they are
 * out of bounds.
 */
bool TileMap::in_bounds(short row, short col)
{
    return !(row >= height || col >= width || row < 0 || col < 0);
}

/**
 * TODO This is really only used to add all the Tile's Rectangle's to the
 * drawable list. Maybe a cleaner solution exists?
 *
 * @return A list of all the Rectangle's used by all the Tile's in
 * this map.
 */
std::vector<Rectangle *> TileMap::get_tile_rects()
{
    std::vector<Rectangle *> rects;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            rects.push_back(at(i, j)->get_rect());
        }
    }

    return rects;
}
