#ifndef CAMERAMOVEEVENT_H
#define CAMERAMOVEEVENT_H

#include "Event.hpp"
#include "Direction.hpp"

/**
 * Handles the movement of the camera.
 */
class CameraMoveEvent : public Event {
private:
    Direction dir;
public:
    /**
     * Create a new CameraMoveEvent in the given Direction.
     *
     * @param dir The Direction this event is moving the camera.
     */
    CameraMoveEvent(Direction dir) { this->dir = dir; }
    virtual Event_Type get_type() { return START_CAMERA_MOVE; }
};

#endif /* CAMERAMOVEEVENT_H */
