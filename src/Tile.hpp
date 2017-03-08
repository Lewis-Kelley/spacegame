#ifndef TILE_H
#define TILE_H

#include <vector>
#include <stdio.h>
#include <stdexcept>

#include "GameState.hpp"
#include "Drawable.hpp"
#include "Direction.hpp"
#include "Entity.hpp"
#include "Listener.hpp"
#include "Event.hpp"
#include "SelectUnitEvent.hpp"
#include "DeselectUnitEvent.hpp"
#include "Rectangle.hpp"

/**
 * Represents a single tile on the game board.
 */
class Tile : public Listener {
private:
    SDL_Color color;
    Rectangle rect;
    short row;
    short col;
    Tile *neighbors[4]; ///< The 4 tiles next to this tile ordered by direction
    std::vector<Entity *> occ_ents; ///< The Entity's in this Tile
    bool in_range;

    void handle_select_unit_event(SelectUnitEvent *event);
    void handle_deselect_unit_event(DeselectUnitEvent *event);
    void define_range(short move_range);
public:
    Tile(short row, short col);
    virtual ~Tile() { }
    void set_neighbor(Direction dir, Tile *neighbor);
    void add_neighbor(Direction dir, Tile *neighbor);
    Tile *get_neighbor(Direction dir);
    void add_entity(Entity *ent);
    bool remove_entity(Entity *ent);
    bool move_entity(Entity *ent, Direction dir);
    bool accepts_entity(Entity *ent);

    /**
     * @return The vector of all Entity's occupying this Tile.
     */
    std::vector<Entity *> get_occ_ents() { return occ_ents; }

    /**
     * @return The row this Tile currently occupies.
     */
    short get_row() { return row; }

    /**
     * @return The column this Tile currently occupies.
     */
    short get_col() { return col; }

    /**
     * @return The Rectangle held by this Tile.
     */
    Rectangle *get_rect() { return &rect; }

    void catch_event(Event *event);
};

#endif /* TILE_H */
