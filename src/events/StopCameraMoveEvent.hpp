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
    StopCameraMoveEvent() { }

    /**
     * Create a new StopCameraMoveEvent in the given Direction.
     *
     * @param dir The Direction this event is moving the camera.
     */
    explicit StopCameraMoveEvent(Direction dir) { this->dir = dir; }

    /**
     * @return The Direction of motion this event stops.
     */
    Direction get_dir() { return dir; }
};

#endif /* STOPCAMERAMOVEEVENT_H */
