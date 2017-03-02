#include "CameraMoveEvent.hpp"

/**
 * @return The dx related to this CameraMovEvent.
 */
double CameraMoveEvent::get_dx()
{
    if (dir & EAST) {
        return -speed;
    }

    if (dir & WEST) {
        return speed;
    }

    return 0.0;
}

/**
 * @return The dy related to this CameraMovEvent.
 */
double CameraMoveEvent::get_dy()
{
    if (dir & NORTH) {
        return speed;
    }

    if (dir & SOUTH) {
        return -speed;
    }

    return 0.0;
}
