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
    this->width = width;
    this->height = height;
    tiles = new Tile *[width * height]();

    set(new Tile(0, 0), 0, 0);
    for (short col = 1; col < width; col++) {
        set(new Tile(0, col), 0, col);
        at(0, col)->add_neighbor(WEST, at(0, col - 1));
    }

    for (short row = 1; row < height; row++) {
        set(new Tile(row, 0), row, 0);
        at(row, 0)->add_neighbor(NORTH, at(row - 1, 0));

        for (short col = 1; col < width; col++) {
            set(new Tile(row, col), row, col);
            at(row, col)->add_neighbor(NORTH, at(row - 1, col));
            at(row, col)->add_neighbor(WEST, at(row, col - 1));
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
