#ifndef CAMERAMOVEEVENT_H
#define CAMERAMOVEEVENT_H

#include "Event.hpp"
#include "../util/Direction.hpp"

#define CAMERA_SPEED 0.1
#define ONE_OVER_SQRT2 0.707106781188

/**
 * Handles the movement of the camera.
 */
class CameraMoveEvent : public Event {
 private:
    double speed;
    Direction dir;

 public:
    CameraMoveEvent() { }

    /**
     * Create a new CameraMoveEvent in the given Direction.
     *
     * @param dir The Direction this event is moving the camera.
     */
    explicit CameraMoveEvent(Direction dir) : speed(CAMERA_SPEED), dir(dir) { }

    /**
     * Create a new CameraMoveEvent in the given Direction with the provided
     * speed.
     *
     * @param speed The amount to move the camera in pixels per second.
     * @param dir The Direction this event is moving the camera.
     */
    CameraMoveEvent(double speed, Direction dir) : speed(speed), dir(dir) { }

    /**
     * @return The Direction this camera movement corresponds to.
     */
    Direction get_dir() { return dir; }

    double get_dx();
    double get_dy();
};

#endif /* CAMERAMOVEEVENT_H */
