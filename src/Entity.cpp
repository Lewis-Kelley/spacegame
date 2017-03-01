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
Entity::Entity(Tile *tile, TileDrawable *img)
{
    occ_tile = tile;
    image = img;
    occ_tile->add_entity(this);
}

double Entity::get_draw_x()
{
    if (image != NULL) {
        return image->get_draw_x();
    }

    NoDrawableException ex;
    throw ex;
}

double Entity::get_draw_y()
{
    if (image != NULL) {
        return image->get_draw_y();
    }

    NoDrawableException ex;
    throw ex;
}
void Entity::set_draw_x(double x)
{
    if (image != NULL) {
        image->set_draw_x(x);
    }

    NoDrawableException ex;
    throw ex;
}

void Entity::set_draw_y(double y)
{
    if (image != NULL) {
        image->set_draw_y(y);
    }

    NoDrawableException ex;
    throw ex;
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
    std::vector<Entity *> neighbors = occ_tile->get_occ_ents();

    for (int i = 0; i < (int)neighbors.size(); i++) {
        if (neighbors.at(i) != this && neighbors.at(i)->blocks_ent(this)) {
            return false;
        }
    }

    return true;
}
