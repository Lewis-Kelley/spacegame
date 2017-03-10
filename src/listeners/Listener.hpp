#ifndef LISTENER_H
#define LISTENER_H

#include <SDL2/SDL.h>

#include "../events/Event.hpp"

/**
 * Abstract class representing all things that want to be triggered
 * upon some SDL_Event.
 */
class Listener {
public:
    /**
     * Handles whatever SDL_Event it expects to get. The
     * implementation is heavily dependent on the specific instance.
     *
     * @param event The SDL_Event to handle.
     */
    virtual void catch_event(Event *event) = 0;
};

#endif /* LISTENER_H */
