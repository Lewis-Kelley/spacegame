#include "TileMap.hpp"

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

Tile *TileMap::at(short row, short col)
{
    if (in_bounds(row, col)) {
        return tiles[row * width + col];
    }

    OutOfBounds ex;
    throw ex;
}

void TileMap::set(Tile *tile, short row, short col)
{
    if (in_bounds(row, col)) {
        tiles[row * width + col] = tile;
        return;
    }

    OutOfBounds ex;
    throw ex;
}

bool TileMap::in_bounds(short row, short col)
{
    return !(row >= height || col >= width || row < 0 || col < 0);
}
