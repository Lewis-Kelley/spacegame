#ifndef STOPCAMERAMOVEEVENT_H
#define STOPCAMERAMOVEEVENT_H

#include "Event.hpp"
#include "../util/Direction.hpp"

/**
 * Handles the ending of moving the camera.
 */
class StopCameraMoveEvent : public Event {
private:
    Direction dir;
public:
    /**
     * Create a new StopCameraMoveEvent in the given Direction.
     *
     * @param dir The Direction this event is moving the camera.
     */
    StopCameraMoveEvent(Direction dir) { this->dir = dir; }
    virtual Event_Type get_type() { return STOP_CAMERA_MOVE; }

    /**
     * @return The Direction of motion this event stops.
     */
    Direction get_dir() { return dir; }
};

#endif /* STOPCAMERAMOVEEVENT_H */
