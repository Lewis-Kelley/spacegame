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
    DrawableDecorator::update(delta);
    rem_x -= curr_movement.dx * delta;
    rem_y -= curr_movement.dy * delta;

    // Check if we overshot (checking for same sign)
    if (rem_x * curr_movement.dx < 0 || rem_y * curr_movement.dy < 0) {
        DrawableDecorator::move(rem_x, rem_y);
        events::event_queue.push(new MoveFinishedEvent());
        kill_move();
    }
}

/**
 * Starts a move for a certain number of tiles at some speed.
 *
 * @param speed The number of pixels to move per second.
 * @param num_tiles The number of tiles to move in the given
 * direction or -1 if should continue endlessly.
 * @param dir The Direction in which to move.
 */
void TileDrawable::start_tile_move(double speed, int num_tiles, Direction dir)
{
    double base_goal;
    double *rem_goal;
    double *rem_other;
    double *d_goal;
    double *d_other;
    int sign = (dir == EAST || dir == SOUTH ? 1 : -1);

    if (dir == EAST || dir == WEST) {
        base_goal = get_draw_x();
        rem_goal = &rem_x;
        rem_other = &rem_y;
        d_goal = &curr_movement.dx;
        d_other = &curr_movement.dy;
    } else {
        base_goal = get_draw_y();
        rem_goal = &rem_y;
        rem_other = &rem_x;
        d_goal = &curr_movement.dy;
        d_other = &curr_movement.dx;
    }

    if (!NEAR_ZERO(*d_other)) {
        AlreadyMovingException ex;
        throw ex;
    }

    if (NEAR_ZERO(*d_goal)) {
        *rem_goal = base_goal;
    }
    *rem_goal = sign * (num_tiles != -1 ? num_tiles : MAX_TILES) * tile_width;
    *rem_other = 0;

    *d_goal = sign * speed;
    *d_other = 0;

    DrawableDecorator::start_move(&curr_movement, MOVEMENT);
}

/**
 * Immediately halts whatever movement is going on.
 */
void TileDrawable::kill_move()
{
    DrawableDecorator::end_move(MOVEMENT);
    rem_x = 0;
    rem_y = 0;
    curr_movement.dx = 0;
    curr_movement.dy = 0;
}
