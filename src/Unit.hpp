#ifndef UNIT_H
#define UNIT_H

#include <string>

#include "Drawable.hpp"
#include "Entity.hpp"
#include "Attack.hpp"
#include "TileDrawable.hpp"

class TileMap;

/**
 * An entity that has stats and can be attacked
 */
class Unit : public Entity {
private:
    std::string team_name;
public:
    Unit(TileMap *tilemap, short row, short col);
    Unit(TileMap *tilemap, short row, short col, TileDrawable *img);
    Unit(double tile_width, TileMap *tilemap, short row, short col,
         Drawable *img);
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

    virtual bool stops_ent(Entity *other);
    virtual bool blocks_ent(Entity *other) { return true; };

    /**
     * Sets the team name for this Unit.
     *
     * @param name The std::string to set the team_name to.
     */
    virtual void set_team_name(std::string name) { team_name = name; }

    /**
     * @return The name of the team this Unit is a member of.
     */
    virtual std::string get_team_name() { return team_name; }

    bool is_unit() { return true; }
};

#include "TileMap.hpp"

#endif /* UNIT_H */
