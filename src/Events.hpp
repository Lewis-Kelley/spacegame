#ifndef EVENTS_H
#define EVENTS_H

#include <SDL2/SDL.h>
#include <map>
#include <stdexcept>
#include <queue>

#include "Event.hpp"
#include "QuitEvent.hpp"
#include "MoveEvent.hpp"

namespace events {
    extern std::map<SDL_Keycode, Event::Event_Type> key_up_map;
    extern std::map<SDL_Keycode, Event::Event_Type> key_dwn_map;
    extern std::map<Event::Event_Type, Event *(*)()> event_fact_map;
    extern std::queue<Event *> event_queue;
    void fill_defaults();
    Event *convert_SDL_Event(SDL_Event *sdl_event);
}

#endif /* EVENTS_H */
