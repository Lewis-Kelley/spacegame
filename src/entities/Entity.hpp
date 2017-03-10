#ifndef ENTITY_H
#define ENTITY_H

#include <stdlib.h>
#include <exception>

#include "../drawables/Drawable.hpp"
#include "../drawables/DrawableDecorator.hpp"
#include "../drawables/TileDrawable.hpp"
#include "../attacks/Attack.hpp"
#include "../util/Direction.hpp"

class Tile;
class Unit;

/**
 * Represents any entity that can occupy a tile. It may or may not be
 * attackable, mobile, or anything else. All it does is exists in one
 * tile on the board.
 */
class Entity : public DrawableDecorator {
protected:
    Tile *occ_tile; ///< The tile this entity occupies
public:
    Entity(Tile *tile);
    Entity(Tile *tile, TileDrawable *img);

    /**
     * Creates a new attack object with target as the target of the
     * attack.
     *
     * @param target The targeted unit in the attack.
     * @return A new attack object filled with all the pertinent
     * information about the attack.
     */
    virtual Attack *make_attack(Unit *target) = 0;

    virtual bool move_ent(Direction dir);

    /**
     * Checks if the passed Entity should be allowed to pass through
     * the Tile this Entity is occupying.
     *
     * @param other The Entity to check against.
     * @return True if this Entity prevents other from passing
     * through, false otherwise.
     */
    virtual bool stops_ent(Entity *other) = 0;

    /**
     * Checks if the passed Entity should be allowed to stop in
     * the Tile this Entity is occupying.
     *
     * @param other The Entity to check against.
     * @return True if this Entity prevents other from stopping in
     * this Enity's Tile, false otherwise.
     */
    virtual bool blocks_ent(Entity *other) = 0;

    /**
     * @return True if this Entity is a Unit, false otherwise.
     */
    virtual bool is_unit() { return false; }

    virtual bool can_stop();
};
#include "../tiles/Tile.hpp"
#include "Unit.hpp"

#endif /* ENTITY_H */
