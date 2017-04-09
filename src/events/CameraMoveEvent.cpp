#include "CameraMoveEvent.hpp"

/**
 * @return The dx related to this CameraMovEvent.
 */
double CameraMoveEvent::get_dx()
{
    double ret_speed = 0.0;

    if (has_direction(dir, EAST)) {
        ret_speed = -speed;
    }

    if (has_direction(dir, WEST)) {
        ret_speed = speed;
    }

    if (has_direction(dir, NORTH) || has_direction(dir, SOUTH)) {
        ret_speed *= ONE_OVER_SQRT2;
    }

    return ret_speed;
}

/**
 * @return The dy related to this CameraMovEvent.
 */
double CameraMoveEvent::get_dy()
{
    double ret_speed = 0.0;

    if (has_direction(dir, SOUTH)) {
        ret_speed = -speed;
    }

    if (has_direction(dir, NORTH)) {
        ret_speed = speed;
    }

    if (has_direction(dir, EAST) || has_direction(dir, WEST)) {
        ret_speed *= ONE_OVER_SQRT2;
    }

    return ret_speed;
}
