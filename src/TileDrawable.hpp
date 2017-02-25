#ifndef TILEDRAWABLE_H
#define TILEDRAWABLE_H

#include <stdio.h>
#include <exception>

#include "DrawableDecorator.hpp"
#include "Direction.hpp"
#include "Events.hpp"
#include "StopMoveEvent.hpp"

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
    double tile_width; ///< The width of an onscreen Tile
    double dx; ///< The shift in the x direction each tick.
    double dy; ///< The shift in the y direction each tick.
    double end_x; ///< The target x location for a move.
    double end_y; ///< The target y location for a move.
public:
    TileDrawable(double tile_width, Drawable *inner);
    void update(double delta);
    void start_move(double speed, int num_tiles, Direction dir);
    void stop_move();
};

#endif /* TILEDRAWABLE_H */
