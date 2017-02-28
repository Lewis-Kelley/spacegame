#ifndef EVENTS_H
#define EVENTS_H

#include <SDL2/SDL.h>
#include <map>
#include <stdexcept>
#include <queue>

#include "Event.hpp"
#include "QuitEvent.hpp"
#include "MoveEvent.hpp"
#include "StopMoveEvent.hpp"
#include "CameraMoveEvent.hpp"
#include "StopCameraMoveEvent.hpp"

namespace events {
    extern std::map<SDL_EventType, Event *(*)(SDL_Event *)> sdl_event_map;
    extern std::map<SDL_Keycode, Event *(*)()> key_dwn_map;
    extern std::map<SDL_Keycode, Event *(*)()> key_up_map;
    extern std::queue<Event *> event_queue;

    void fill_defaults();
    Event *convert_SDL_Event(SDL_Event *sdl_event);

    template <std::map<SDL_Keycode, Event *(*)()> *keymap>
    Event *handle_key(SDL_Event *sdl_event);
}

#endif /* EVENTS_H */
