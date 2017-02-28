#include "CameraMoveEvent.hpp"

/**
 * @return The dx related to this CameraMovEvent.
 */
double CameraMoveEvent::get_dx()
{
    if (dir & EAST) {
        return -CAMERA_SPEED;
    }

    if (dir & WEST) {
        return CAMERA_SPEED;
    }

    return 0.0;
}

/**
 * @return The dy related to this CameraMovEvent.
 */
double CameraMoveEvent::get_dy()
{
    if (dir & NORTH) {
        return CAMERA_SPEED;
    }

    if (dir & SOUTH) {
        return -CAMERA_SPEED;
    }

    return 0.0;
}
