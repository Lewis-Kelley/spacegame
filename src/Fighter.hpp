#ifndef FIGHTER_H
#define FIGHTER_H

#include "EventHandler.hpp"
#include "StopMoveEvent.hpp"
#include "MoveEvent.hpp"
#include "Unit.hpp"
#include "Listener.hpp"
#include "Sprite.hpp"
#include "TileDrawable.hpp"
#include "CameraMoveEvent.hpp"
#include "StopCameraMoveEvent.hpp"
#include "SelectUnitEvent.hpp"
#include "DeselectUnitEvent.hpp"

/**
 * The standard Fighter Unit that will be the primary game board Unit.
 */
class Fighter : public Unit, public Listener {
private:
    short hull_health;
    short shield_health;
    short engine_health;
    short weapon_health;
    short total_power;
    short shield_power;
    short engine_power;
    short weapon_power;

    void init();
public:
    Fighter(TileMap *tilemap, short row, short col, TileDrawable *img);
    Fighter(double tile_width, TileMap *tilemap, short row, short col,
            Drawable *img);
    Fighter(Tile *tile, TileDrawable *img);
    short get_hull_health() { return hull_health; }
    short get_shield_health() { return shield_health; }
    short get_engine_health() { return engine_health; }
    short get_weapon_health() { return weapon_health; }
    short get_total_power() { return total_power; }
    short get_shield_power() { return shield_power; }
    short get_engine_power() { return engine_power; }
    short get_weapon_power() { return weapon_power; }
    Attack *make_attack(Unit *target);
    short get_move_range();
    std::pair<short, short> get_attack_range();
    void handle_attack(Attack *att);
    void catch_event(Event *event);
};

#endif /* FIGHTER_H */
