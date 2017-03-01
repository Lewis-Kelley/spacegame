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

#define MOVE_SPEED 0.25

/**
 * The standard Fighter Unit that will be the primary game board Unit.
 */
class Fighter : public Unit, public Listener {
private:
    Direction moving_dir;
    Direction camera_dir;
    short hull_health;
    short shield_health;
    short engine_health;
    short weapon_health;
    short total_power;
    short shield_power;
    short engine_power;
    short weapon_power;

    void handle_move_event(MoveEvent *event);
    void handle_stop_event(StopMoveEvent *event);
    void handle_move_finished_event(MoveFinishedEvent *event);
    void handle_camera_move_event(CameraMoveEvent *event);
    void handle_camera_stop_move_event(StopCameraMoveEvent *event);
    void handle_select_unit_event(SelectUnitEvent *event);
    void handle_deselect_unit_event(DeselectUnitEvent *event);
public:
    Fighter(TileMap *tilemap, short row, short col, TileDrawable *img);
    Fighter(double tile_width, TileMap *tilemap, short row, short col,
            Drawable *img);
    Fighter(Tile *tile, TileDrawable *img);
    virtual short get_hull_health() { return hull_health; }
    virtual short get_shield_health() { return shield_health; }
    virtual short get_engine_health() { return engine_health; }
    virtual short get_weapon_health() { return weapon_health; }
    virtual short get_total_power() { return total_power; }
    virtual short get_shield_power() { return shield_power; }
    virtual short get_engine_power() { return engine_power; }
    virtual short get_weapon_power() { return weapon_power; }
    virtual Attack *make_attack(Unit *target);
    virtual short get_move_range();
    virtual void handle_attack(Attack *att);
    virtual void catch_event(Event *event);
    bool move_fighter(Direction dir);
};

#endif /* FIGHTER_H */
