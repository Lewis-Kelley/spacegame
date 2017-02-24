#ifndef ENTITY_H
#define ENTITY_H

#include <stdlib.h>

#include "Drawable.hpp"
#include "Attack.hpp"

class Tile;
class Unit;

/**
 * Represents any entity that can occupy a tile. It may or may not be
 * attackable, mobile, or anything else. All it does is exists in one
 * tile on the board.
 */
class Entity : public Drawable {
private:
    Drawable *image; ///< The image representing this entity or NULL if none
    Tile *occ_tile; ///< The tile this entity occupies
public:
    Entity();
    Entity(Drawable *img);

    /**
     * Draws this entity on the screen if there is one to be drawn.
     *
     * @return True if successful or there is no image representing
     * this entity. False otherwise.
     */
    bool draw() { return (image == NULL) ? true : image->draw(); }

    /**
     * Creates a new attack object with target as the target of the
     * attack.
     *
     * @param target The targeted unit in the attack.
     * @return A new attack object filled with all the pertinent
     * information about the attack.
     */
    virtual Attack *make_attack(Unit *target) = 0;
};
#include "Tile.hpp"
#include "Unit.hpp"

#endif /* ENTITY_H */
