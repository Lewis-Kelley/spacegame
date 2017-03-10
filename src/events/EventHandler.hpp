#ifndef EVENT_HANDLER_H
#define EVENT_HANDLER_H

#include <SDL2/SDL.h>
#include <map>
#include <vector>
#include <stdexcept>

#include "Event.hpp"
#include "../listeners/Listener.hpp"

namespace event_handler {
    extern std::map<Event::Event_Type, std::vector<Listener *>*> listeners;

    void handle_event(Event *event);
    void add_listener(Event::Event_Type type, Listener *obs);
    void remove_listener(Event::Event_Type type, Listener *obs);
}

#endif
