#ifndef TILEMAP_H
#define TILEMAP_H

#include <stdint.h>
#include <stdexcept>
#include <vector>

#include "../events/EventHandler.hpp"
#include "Tile.hpp"
#include "../drawables/Rectangle.hpp"

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
    uint16_t width;
    uint16_t height;

    bool in_bounds(uint16_t row, uint16_t col);
 public:
    TileMap(uint16_t width, uint16_t height);
    ~TileMap();
    Tile *at(uint16_t row, uint16_t col);
    void set(Tile *tile, uint16_t row, uint16_t col);
    std::vector<Rectangle *> get_tile_rects();
};

#endif /* TILEMAP_H */
