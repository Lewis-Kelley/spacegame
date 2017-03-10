#ifndef TILEDRAWABLE_H
#define TILEDRAWABLE_H

#include <stdio.h>
#include <exception>

#include "DrawableDecorator.hpp"
#include "../util/Direction.hpp"
#include "../events/Events.hpp"
#include "../events/MoveFinishedEvent.hpp"

/**
 * A decorator that handles drawings that are bound to tiles.
 */
class TileDrawable : public DrawableDecorator {
private:
    class AlreadyMovingException : public std::exception {
        virtual const char* what() const throw()
        {
            return "This Drawable is already moving perpendicularly!\n";
        }
    };
    Movement curr_movement;
    double tile_width; ///< The width of an onscreen Tile
    double rem_x;
    double rem_y;
public:
    TileDrawable(double tile_width, Drawable *inner, short row, short col);
    void update(double delta);
    void start_tile_move(double speed, int num_tiles, Direction dir);
    void kill_move();
};

#endif /* TILEDRAWABLE_H */
