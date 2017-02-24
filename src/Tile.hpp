#ifndef TILE_H
#define TILE_H

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
    /*
      FIXME What if there are multiple entities in this tile? They're
      not guaranteed to be exclusive from each other.
     */
    Entity *occ_ent; ///< The entity currently occupying this tile
    Entity *trans_ent; ///< An entity currently passing through this tile
public:
    Tile();
};

#endif /* TILE_H */
