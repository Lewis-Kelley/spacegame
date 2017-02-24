#include "Entity.hpp"

/**
 * Initializes the entity, binding it to a tile while not providing it
 * an image.
 *
 * @param tile The tile this Entity occupies.
 */
Entity::Entity(Tile *tile)
{
    occ_tile = tile;
    image = NULL;
    occ_tile->add_entity(this);
}

/**
 * Initializes the entity binding it to a tile while providing it an
 * image.
 *
 * @param tile The tile this Entity occupies.
 * @param img The drawable that will represent this entity.
 */
Entity::Entity(Tile *tile, Drawable *img)
{
    occ_tile = tile;
    image = img;
    occ_tile->add_entity(this);
}

/**
 * Move this Entity to the Tile in the given Direction.
 *
 * @param dir The Direction in which to move this Entity.
 * @return True if successfully moved, false if the process failed.
 */
bool Entity::move(Direction dir)
{
    return occ_tile->move_entity(this, dir);
}
