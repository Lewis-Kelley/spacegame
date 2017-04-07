#ifndef TILE_H
#define TILE_H

#include <stdint.h>
#include <stdio.h>
#include <stdexcept>
#include <vector>

#include "../util/GameState.hpp"
#include "../drawables/Drawable.hpp"
#include "../util/Direction.hpp"
#include "../entities/Entity.hpp"
#include "../listeners/Listener.hpp"
#include "../events/Event.hpp"
#include "../events/SelectUnitEvent.hpp"
#include "../events/DeselectUnitEvent.hpp"
#include "../drawables/Rectangle.hpp"

/**
 * Represents a single tile on the game board.
 */
class Tile {
 private:
    class SelectUnitListener : public Listener {
     private:
        Tile *outer;

     public:
        SelectUnitListener(Tile *outer) : outer(outer) { }
        virtual ~SelectUnitListener() { }
        void catch_event(Event *);
    } select_listener;

    class DeselectUnitListener : public Listener {
     private:
        Tile *outer;

     public:
        DeselectUnitListener(Tile *outer) : outer(outer) { }
        virtual ~DeselectUnitListener() { }
        void catch_event(Event *);
    } deselect_listener;

    SDL_Color color;
    Rectangle rect;
    uint16_t row;
    uint16_t col;
    Tile *neighbors[4];  ///< The 4 tiles next to this tile ordered by direction
    std::vector<Entity *> occ_ents;  ///< The Entity's in this Tile
    bool in_range;

    void define_range(Entity *ent, uint16_t move_range);

 public:
    Tile(uint16_t row, uint16_t col);
    virtual ~Tile() { }
    void set_neighbor(Direction dir, Tile *neighbor);
    void add_neighbor(Direction dir, Tile *neighbor);
    Tile *get_neighbor(Direction dir);
    void add_entity(Entity *ent);
    bool remove_entity(Entity *ent);
    bool move_entity(Entity *ent, Direction dir);
    bool accepts_entity(Entity *ent);
    bool stops_entity(Entity *ent);

    /**
     * @return The vector of all Entity's occupying this Tile.
     */
    std::vector<Entity *> get_occ_ents() { return occ_ents; }

    /**
     * @return The row this Tile currently occupies.
     */
    uint16_t get_row() { return row; }

    /**
     * @return The column this Tile currently occupies.
     */
    uint16_t get_col() { return col; }

    /**
     * @return The Rectangle held by this Tile.
     */
    Rectangle *get_rect() { return &rect; }
};

#endif /* TILE_H */
