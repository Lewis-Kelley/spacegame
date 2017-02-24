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
        START_MOVE_EAST,
        START_MOVE_NORTH,
        START_MOVE_WEST,
        START_MOVE_SOUTH,
        END_MOVE_EAST,
        END_MOVE_NORTH,
        END_MOVE_WEST,
        END_MOVE_SOUTH,
        MOUSE_MOTION,
        MOUSE_LEFT_CLICK,
        MOUSE_RIGHT_CLICK,
        MOUSE_MIDDLE_CLICK,
        MOUSE_LEFT_RELEASE,
        MOUSE_RIGHT_RELEASE,
        MOUSE_MIDDLE_RELEASE
    };

    virtual ~Event() { }

    /**
     * @return Whatever type this specific Event is.
     */
    virtual Event_Type get_type() = 0;
};

#endif /* EVENT_H */
