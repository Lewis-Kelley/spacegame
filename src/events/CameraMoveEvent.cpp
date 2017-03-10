#include "CameraMoveEvent.hpp"

/**
 * @return The dx related to this CameraMovEvent.
 */
double CameraMoveEvent::get_dx()
{
    if (has_direction(dir, EAST)) {
        return -speed;
    }

    if (has_direction(dir, WEST)) {
        return speed;
    }

    return 0.0;
}

/**
 * @return The dy related to this CameraMovEvent.
 */
double CameraMoveEvent::get_dy()
{
    if (has_direction(dir, NORTH)) {
        return speed;
    }

    if (has_direction(dir, SOUTH)) {
        return -speed;
    }

    return 0.0;
}
