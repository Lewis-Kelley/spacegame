#ifndef EVENT_H
#define EVENT_H

/**
 * Abstract Event type that will be passed around to different game
 * entities to handle.
 */
class Event {
 public:
    virtual ~Event() { }
};

#endif /* EVENT_H */
