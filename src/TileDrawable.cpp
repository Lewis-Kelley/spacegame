#include "TileDrawable.hpp"

/**
 * Initializes the TileDrawable with the given parameters.
 *
 * @param tile_width The onscreen width of a Tile
 * @param inner The inner Drawable
 */
TileDrawable::TileDrawable(double tile_width, Drawable *inner)
    : DrawableDecorator(inner), tile_width(tile_width) { }

/**
 * Move the sprite according to its dx, dy, and the time passed.
 *
 * @param delta The amount of time passed since the last tick.
 */
void TileDrawable::update(double delta)
{
    Drawable::move(dx * delta, dy * delta);

    if (dx * (get_draw_x() - end_x) > 0) {
        events::event_queue.push(new StopMoveEvent(dx > 0 ? EAST : WEST));
        set_draw_x(end_x);
        dx = 0;
    }

    if (dy * (get_draw_y() - end_y) > 0) {
        events::event_queue.push(new StopMoveEvent(dy > 0 ? NORTH : NORTH));
        set_draw_y(end_y);
        dy = 0;
    }
}

/**
 * Starts a move for a certain number of tiles at some speed.
 *
 * @param speed The number of pixels to move per second.
 * @param num_tiles The number of tiles to move in the given
 * direction.
 * @param dir The Direction in which to move.
 */
void TileDrawable::start_move(double speed, int num_tiles, Direction dir)
{
    double base_goal;
    double base_other;
    double *end_goal;
    double *end_other;
    double *d_goal;
    double *d_other;
    int sign = (dir == EAST || dir == SOUTH ? 1 : -1);

    if (dir == EAST || dir == WEST) {
        base_goal = get_draw_x();
        base_other = get_draw_y();
        end_goal = &end_x;
        end_other = &end_y;
        d_goal = &dx;
        d_other = &dy;
    } else {
        base_goal = get_draw_y();
        base_other = get_draw_x();
        end_goal = &end_y;
        end_other = &end_x;
        d_goal = &dy;
        d_other = &dx;
    }

    if (*d_other != 0) {
        AlreadyMovingException ex;
        throw ex;
    }

    if (*d_goal == 0) {
        *end_goal = base_goal;
    }
    *end_goal += sign * num_tiles * tile_width;
    *end_other = base_other;

    *d_goal = sign * speed;
    *d_other = 0;
}

/**
 * Immediately halts whatever movement is going on.
 */
void TileDrawable::stop_move()
{
    dx = 0;
    dy = 0;
    end_x = get_draw_x();
    end_y = get_draw_y();
}
