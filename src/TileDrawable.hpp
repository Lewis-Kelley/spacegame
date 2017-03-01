#ifndef TILEDRAWABLE_H
#define TILEDRAWABLE_H

#include <stdio.h>
#include <exception>

#include "DrawableDecorator.hpp"
#include "Direction.hpp"
#include "Events.hpp"
#include "MoveFinishedEvent.hpp"

#define ABS(x) (x > 0 ? x : -x)
#define MAX_TILES 500
#define ROUNDOFF 0.0001
#define NEAR_ZERO(x) (ABS(x) < ROUNDOFF)

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
    TileDrawable(double tile_width, Drawable *inner);
    void update(double delta);
    void start_tile_move(double speed, int num_tiles, Direction dir);
    void kill_move();

    /**
     * @return True if this is still animating a motion, false
     * otherwise.
     */
    bool is_moving() { return !NEAR_ZERO(curr_movement.dx)
            || !NEAR_ZERO(curr_movement.dy); }
};

#endif /* TILEDRAWABLE_H */
