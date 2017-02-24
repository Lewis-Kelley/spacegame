#include "Entity.hpp"

/**
 * Initializes the entity without binding it to a tile nor providing
 * it an image.
 */
Entity::Entity() {
    occ_tile = NULL;
    image = NULL;
}

/**
 * Initializes the entity without binding it to a tile while providing
 * it an image.
 *
 * @param img The drawable that will represent this entity.
 */
Entity::Entity(Drawable *img) {
    occ_tile = NULL;
    image = img;
}
