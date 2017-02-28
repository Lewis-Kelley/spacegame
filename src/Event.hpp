#ifndef EVENT_H
#define EVENT_H

/**
 * Abstract Event type that will be passed around to different game
 * entities to handle.
 */
class Event {
public:
    /**
     * Kind of klunky, but the list of the different types of events
     * an abstract event can be.
     */
    enum Event_Type {
        NONE,
        QUIT,
        START_UNIT_MOVE,
        END_UNIT_MOVE,
        MOUSE_MOTION,
        MOUSE_LEFT_CLICK,
        MOUSE_RIGHT_CLICK,
        MOUSE_MIDDLE_CLICK,
        MOUSE_LEFT_RELEASE,
        MOUSE_RIGHT_RELEASE,
        MOUSE_MIDDLE_RELEASE,
        UNIT_MOVE_FINISHED,
        START_CAMERA_MOVE,
        STOP_CAMERA_MOVE
    };

    virtual ~Event() { }

    /**
     * @return Whatever type this specific Event is.
     */
    virtual Event_Type get_type() = 0;
};

#endif /* EVENT_H */
