#ifndef TILEMAP_H
#define TILEMAP_H

#include <stdexcept>
#include <vector>

#include "EventHandler.hpp"
#include "Tile.hpp"
#include "Rectangle.hpp"

/**
 * Holds a full grid of Tile's.
 */
class TileMap {
private:
    class OutOfBounds : public std::exception {
        virtual const char* what() const throw()
        {
            return "The passed coordinates are out of bounds.\n";
        }
    };

    Tile **tiles;
    short width;
    short height;

    bool in_bounds(short row, short col);
public:
    TileMap(short width, short height);
    ~TileMap();
    Tile *at(short row, short col);
    void set(Tile *tile, short row, short col);
    std::vector<Rectangle *> get_tile_rects();
};

#endif /* TILEMAP_H */
