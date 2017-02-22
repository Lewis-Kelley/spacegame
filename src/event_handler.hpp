#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include <map>
#include <vector>

#include "listener.hpp"

/**
 * Handles SDL_Event's.
 */
class event_handler {
private:
    static event_handler *self;
    std::map<uint32_t,  std::vector<listener *> > listeners;

    event_handler();
public:
    static event_handler *get_instance();
    void handle_event(SDL_Event *event);
    void add_listener(uint32_t event_code, listener *obs);
    void remove_listener(uint32_t event_code, listener *obs);
};

#endif
