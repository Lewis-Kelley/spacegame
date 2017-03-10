#include "Entity.hpp"

/**
 * Initializes the entity, binding it to a tile while not providing it
 * an image.
 *
 * @param tile The tile this Entity occupies.
 */
Entity::Entity(Tile *tile) : DrawableDecorator(NULL)
{
    occ_tile = tile;
    occ_tile->add_entity(this);
}

/**
 * Initializes the entity binding it to a tile while providing it an
 * image.
 *
 * @param tile The tile this Entity occupies.
 * @param img The drawable that will represent this entity.
 */
Entity::Entity(Tile *tile, TileDrawable *img) : DrawableDecorator(img)
{
    occ_tile = tile;
    occ_tile->add_entity(this);
}

/**
 * Move this Entity to the Tile in the given Direction.
 *
 * @param dir The Direction in which to move this Entity.
 * @return True if successfully moved, false if the process failed.
 */
bool Entity::move_ent(Direction dir)
{
    return occ_tile->move_entity(this, dir);
}


/**
 * @return True if this Entity can stop in the Tile it currently
 * occupies, false otherwise.
 */
bool Entity::can_stop()
{
    for (Entity *other_ent : occ_tile->get_occ_ents()) {
        if (other_ent != this && other_ent->blocks_ent(this)) {
            return false;
        }
    }

    return true;
}
