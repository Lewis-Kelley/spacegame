#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <utility>

#include "../drawables/Drawable.hpp"
#include "Entity.hpp"
#include "../attacks/Attack.hpp"
#include "../drawables/TileDrawable.hpp"

#define MOVE_SPEED 0.25

class TileMap;

/**
 * An entity that has stats and can be attacked
 */
class Unit : public Entity {
 private:
    std::string team_name;

 public:
    Unit(TileMap *tilemap, int16_t row, int16_t col);
    Unit(TileMap *tilemap, int16_t row, int16_t col, TileDrawable *img);
    Unit(double tile_width, TileMap *tilemap, int16_t row, int16_t col,
         Drawable *img);
    explicit Unit(Tile *tile);
    Unit(Tile *tile, TileDrawable *img);

    /**
     * TODO Check what this means in the design docs.
     *
     * @return The health of the hull of this unit (a.k.a. max energy
     * allocation)
     */
    virtual int16_t get_hull_health() = 0;

    /**
     * @return The health of the shield of this unit. (a.k.a. max
     * energy allocation)
     */
    virtual int16_t get_shield_health() = 0;

    /**
     * @return The health of the engine of this unit. (a.k.a. max
     * energy allocation)
     */
    virtual int16_t get_engine_health() = 0;

    /**
     * @return The health of the weapon of this unit. (a.k.a. max
     * energy allocation)
     */
    virtual int16_t get_weapon_health() = 0;

    /**
     * @return The total available power for this unit, allocated or
     * not.
     */
    virtual int16_t get_total_power() = 0;

    /**
     * @return The power currently allocated to the shield.
     */
    virtual int16_t get_shield_power() = 0;

    /**
     * @return The power currently allocated to the engine.
     */
    virtual int16_t get_engine_power() = 0;

    /**
     * @return The power currently allocated to the weapon.
     */
    virtual int16_t get_weapon_power() = 0;

    /**
     * @return The number of unobstructed tiles this unit can move
     * before any reductions.
     */
    virtual int16_t get_move_range() = 0;

    /**
     * @return A pair of radii from the current Unit, where the first
     * value is the minimum radius and the second the maximum radius.
     */
    virtual std::pair<int16_t, int16_t> get_attack_range() = 0;

    /**
     * Accepts an attack targeted at this unit and handles it in
     * whatever way is appropriate.
     */
    virtual void handle_attack(Attack *att) = 0;

    virtual bool stops_ent(Entity *other);
    virtual bool blocks_ent(Entity *other) { return true; }

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

    virtual bool move_unit(Direction dir);

    bool is_unit() { return true; }
};

#include "../tiles/TileMap.hpp"

#endif /* UNIT_H */
