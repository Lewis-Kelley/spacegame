#ifndef TILE_H
#define TILE_H

#include <vector>
#include <stdio.h>
#include <stdexcept>

#include "Direction.hpp"
#include "Entity.hpp"

/**
 * Represents a single tile on the game board.
 */
class Tile {
private:
    short row;
    short col;
    Tile *neighbors[4]; ///< The 4 tiles next to this tile ordered by direction
    std::vector<Entity *> occ_ents; ///< The Entity's in this Tile
public:
    Tile(short row, short col);
    void set_neighbor(Direction dir, Tile *neighbor);
    void add_neighbor(Direction dir, Tile *neighbor);
    Tile *get_neighbor(Direction dir);
    void add_entity(Entity *ent);
    bool remove_entity(Entity *ent);
    bool move_entity(Entity *ent, Direction dir);
    short get_row() { return row; }
    short get_col() { return col; }
    std::vector<Entity *> get_occ_ents();
};

#endif /* TILE_H */
