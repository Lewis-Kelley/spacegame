#ifndef UNIT_H
#define UNIT_H

#include "Drawable.hpp"
#include "Entity.hpp"
#include "Attack.hpp"
#include "TileDrawable.hpp"

/**
 * An entity that has stats and can be attacked
 */
class Unit : public Entity {
public:
    Unit(Tile *tile);
    Unit(Tile *tile, TileDrawable *img);

    /**
     * TODO Check what this means in the design docs.
     *
     * @return The health of the hull of this unit (a.k.a. max energy
     * allocation)
     */
    virtual short get_hull_health() = 0;

    /**
     * @return The health of the shield of this unit. (a.k.a. max
     * energy allocation)
     */
    virtual short get_shield_health() = 0;

    /**
     * @return The health of the engine of this unit. (a.k.a. max
     * energy allocation)
     */
    virtual short get_engine_health() = 0;

    /**
     * @return The health of the weapon of this unit. (a.k.a. max
     * energy allocation)
     */
    virtual short get_weapon_health() = 0;

    /**
     * @return The total available power for this unit, allocated or
     * not.
     */
    virtual short get_total_power() = 0;

    /**
     * @return The power currently allocated to the shield.
     */
    virtual short get_shield_power() = 0;

    /**
     * @return The power currently allocated to the engine.
     */
    virtual short get_engine_power() = 0;

    /**
     * @return The power currently allocated to the weapon.
     */
    virtual short get_weapon_power() = 0;

    /**
     * @return The number of unobstructed tiles this unit can move
     * before any reductions.
     */
    virtual short get_move_range() = 0;

    /**
     * Accepts an attack targeted at this unit and handles it in
     * whatever way is appropriate.
     */
    virtual void handle_attack(Attack *att) = 0;
};

#endif /* UNIT_H */
