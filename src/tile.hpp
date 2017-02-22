#ifndef TILE_H
#define TILE_H

#include "direction.hpp"
#include "entity.hpp"

/**
 * Represents a single tile on the game board.
 */
class tile {
private:
    short x; ///< The x coordinate of this tile in the board (left = 0)
    short y; ///< The y coordinate of this tile in the board (up = 0)
    tile *neighbors[4]; ///< The 4 tiles next to this tile ordered by direction
    /*
      FIXME What if there are multiple entities in this tile? They're
      not guaranteed to be exclusive from each other.
     */
    entity *occ_ent; ///< The entity currently occupying this tile
    entity *trans_ent; ///< An entity currently passing through this tile
public:
};

#endif /* TILE_H */
