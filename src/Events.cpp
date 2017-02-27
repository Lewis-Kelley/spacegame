#include "Events.hpp"

std::map<SDL_EventType, Event *(*)(SDL_Event *)> events::sdl_event_map;
std::map<SDL_Keycode, Event *(*)()> events::key_dwn_map;
std::map<SDL_Keycode, Event *(*)()> events::key_up_map;
std::queue<Event *> events::event_queue;

Event *events::convert_SDL_Event(SDL_Event *sdl_event)
{
    SDL_EventType type = (SDL_EventType)sdl_event->type;
    if (sdl_event_map.find(type) != sdl_event_map.end()) {
        return sdl_event_map.at(type)(sdl_event);
    }

    return NULL;
}

template <class E>
Event *create_event()
{
    return new E();
}

template <class E, Direction dir>
Event *create_dir_event()
{
    return new E(dir);
}

template <std::map<SDL_Keycode, Event *(*)()> *keymap>
Event *events::handle_key(SDL_Event *sdl_event)
{
    if (keymap->find(sdl_event->key.keysym.sym) != keymap->end()) {
        return keymap->at(sdl_event->key.keysym.sym)();
    }

    return NULL;
}

void events::fill_defaults()
{
    typedef std::pair<SDL_EventType, Event *(*)(SDL_Event *)> event_pair;
    typedef std::pair<SDL_Keycode, Event *(*)()> key_pair;

    sdl_event_map.insert(event_pair(SDL_KEYDOWN, handle_key<&key_dwn_map>));
    sdl_event_map.insert(event_pair(SDL_KEYUP, handle_key<&key_up_map>));

    key_dwn_map.insert(key_pair(SDLK_q, create_event<QuitEvent>));

    key_dwn_map.insert(key_pair(SDLK_RIGHT, create_dir_event<MoveEvent, EAST>));
    key_dwn_map.insert(key_pair(SDLK_UP, create_dir_event<MoveEvent, NORTH>));
    key_dwn_map.insert(key_pair(SDLK_LEFT, create_dir_event<MoveEvent, WEST>));
    key_dwn_map.insert(key_pair(SDLK_DOWN, create_dir_event<MoveEvent, SOUTH>));

    key_dwn_map.insert(key_pair(SDLK_s,
                                create_dir_event<CameraMoveEvent, EAST>));
    key_dwn_map.insert(key_pair(SDLK_w,
                                create_dir_event<CameraMoveEvent, NORTH>));
    key_dwn_map.insert(key_pair(SDLK_a,
                                create_dir_event<CameraMoveEvent, WEST>));
    key_dwn_map.insert(key_pair(SDLK_r,
                                create_dir_event<CameraMoveEvent, SOUTH>));

    key_up_map.insert(key_pair(SDLK_RIGHT,
                               create_dir_event<StopMoveEvent, EAST>));
    key_up_map.insert(key_pair(SDLK_UP,
                               create_dir_event<StopMoveEvent, NORTH>));
    key_up_map.insert(key_pair(SDLK_LEFT,
                               create_dir_event<StopMoveEvent, WEST>));
    key_up_map.insert(key_pair(SDLK_DOWN,
                               create_dir_event<StopMoveEvent, SOUTH>));
}
