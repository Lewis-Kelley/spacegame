#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include <map>
#include <vector>
#include <stdexcept>

#include "Event.hpp"
#include "Listener.hpp"

/**
 * Handles Event's.
 */
class EventHandler {
private:
    static EventHandler *self;
    std::map<Event::Event_Type,  std::vector<Listener *>*> listeners;
    EventHandler();
public:
    static EventHandler *get_instance();
    void handle_event(Event *event);
    void add_listener(Event::Event_Type type, Listener *obs);
    void remove_listener(Event::Event_Type type, Listener *obs);
};

#endif
