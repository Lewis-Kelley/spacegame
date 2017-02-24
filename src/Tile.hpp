#ifndef TILE_H
#define TILE_H

#include <vector>
#include <stdio.h>

#include "Direction.hpp"
#include "Entity.hpp"

/**
 * Represents a single tile on the game board.
 */
class Tile {
private:
    short x; ///< The x coordinate of this tile in the board (left = 0)
    short y; ///< The y coordinate of this tile in the board (up = 0)
    Tile *neighbors[4]; ///< The 4 tiles next to this tile ordered by direction
    std::vector<Entity *> occ_ents; ///< The Entity's in this Tile
public:
    Tile(short x, short y);
    void set_neighbor(Direction dir, Tile *neighbor);
    void add_neighbor(Direction dir, Tile *neighbor);
    Tile *get_neighbor(Direction dir);
    void add_entity(Entity *ent);
    bool remove_entity(Entity *ent);
    bool move_entity(Entity *ent, Direction dir);
};

#endif /* TILE_H */
