#ifndef FIGHTER_H
#define FIGHTER_H

#include <utility>

#include "../events/EventHandler.hpp"
#include "../events/StopMoveEvent.hpp"
#include "../events/MoveEvent.hpp"
#include "Unit.hpp"
#include "../listeners/Listener.hpp"
#include "../drawables/Sprite.hpp"
#include "../drawables/TileDrawable.hpp"
#include "../events/CameraMoveEvent.hpp"
#include "../events/StopCameraMoveEvent.hpp"
#include "../events/SelectUnitEvent.hpp"
#include "../events/DeselectUnitEvent.hpp"

/**
 * The standard Fighter Unit that will be the primary game board Unit.
 */
class Fighter : public Unit, public Listener {
 private:
    int16_t hull_health;
    int16_t shield_health;
    int16_t engine_health;
    int16_t weapon_health;
    int16_t total_power;
    int16_t shield_power;
    int16_t engine_power;
    int16_t weapon_power;

    void init();

 public:
    Fighter(TileMap *tilemap, int16_t row, int16_t col, TileDrawable *img);
    Fighter(double tile_width, TileMap *tilemap, int16_t row, int16_t col,
            Drawable *img);
    Fighter(Tile *tile, TileDrawable *img);
    int16_t get_hull_health() { return hull_health; }
    int16_t get_shield_health() { return shield_health; }
    int16_t get_engine_health() { return engine_health; }
    int16_t get_weapon_health() { return weapon_health; }
    int16_t get_total_power() { return total_power; }
    int16_t get_shield_power() { return shield_power; }
    int16_t get_engine_power() { return engine_power; }
    int16_t get_weapon_power() { return weapon_power; }
    Attack *make_attack(Unit *target);
    int16_t get_move_range();
    std::pair<int16_t, int16_t> get_attack_range();
    void handle_attack(Attack *att);
    void catch_event(Event *event);
};

#endif /* FIGHTER_H */
