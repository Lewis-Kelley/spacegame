#include "Tile.hpp"

/**
 * Create a new tile at the given coordinates.
 *
 * @param x The x coordinate of the tile (left = 0)
 * @param y The y coordinate of the tile (up = 0)
 */
Tile::Tile(short x, short y)
{
    this->x = x;
    this->y = y;

    for (int i = 0; i < 4; i++) {
        neighbors[i] = NULL;
    }
}

/**
 * Sets the neighboring Tile in the given Direction.
 *
 * @param dir The Direction in which to add the Tile.
 * @param neighbor The new neighbor for this Tile.
 */
void Tile::set_neighbor(Direction dir, Tile *neighbor)
{
    neighbors[dir] = neighbor;
}

/**
 * Sets the neighboring Tile in the given Direction, both for this
 * Tile and the neighbor.
 *
 * @param dir The Direction in which to add the Tile.
 * @param neighbor The new neighbor for this Tile.
 */
void Tile::add_neighbor(Direction dir, Tile *neighbor)
{
    set_neighbor(dir, neighbor);
    neighbor->set_neighbor(opp_dir(dir), this);
}

/**
 * Returns the neighboring Tile in the given Direction.
 *
 * @param dir The Direction in which to retrieve the neighbor.
 * @return The neighbor in the given Direction.
 */
Tile *Tile::get_neighbor(Direction dir)
{
    return neighbors[dir];
}

/**
 * Adds the given entity to the list of entities in this Tile.
 *
 * @param ent The Entity to add.
 */
void Tile::add_entity(Entity *ent)
{
    occ_ents.push_back(ent);
}

/**
 * Removes the passed entity from the list of entities in this Tile if
 * it exists.
 *
 * @param ent The Entity to remove.
 * @return True if successfully removed, false if the passed Entity
 * was never there.
 */
bool Tile::remove_entity(Entity *ent)
{
    for (int i = 0; i < (int)occ_ents.size(); i++) {
        if (occ_ents.at(i) == ent) {
            occ_ents.erase(occ_ents.begin() + i);
            return true;
        }
    }

    return false;
}

/**
 * Moves the passed Entity to the neighboring Tile in the given
 * direction.
 *
 * @param ent The Entity to move.
 * @param dir The Direction in which to move the Entity.
 * @return True if successfully moved, false if the passed Entity was
 * never there or if there is no neighboring Tile in that direction.
 */
bool Tile::move_entity(Entity *ent, Direction dir)
{
    Tile *neighbor = get_neighbor(dir);
    if (neighbor != NULL && remove_entity(ent)) {
        neighbor->add_entity(ent);
        return true;
    }

    return false;
}
