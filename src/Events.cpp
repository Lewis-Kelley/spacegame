#include "Events.hpp"

std::map<SDL_Keycode, Event::Event_Type> events::key_up_map;
std::map<SDL_Keycode, Event::Event_Type> events::key_dwn_map;
std::map<Event::Event_Type, Event *(*)()> events::event_fact_map;
std::queue<Event *> events::event_queue;

Event *events::convert_SDL_Event(SDL_Event *sdl_event) {
    Event::Event_Type type = Event::NONE;
    switch(sdl_event->type) {
    case SDL_KEYDOWN:
        try {
            type = events::key_dwn_map.at(sdl_event->key.keysym.sym);
        } catch (std::out_of_range err) {
            fprintf(stderr, "No matching key %d.\n", sdl_event->key.keysym.sym);
        }
        break;
    case SDL_KEYUP:
        try {
            type = events::key_up_map.at(sdl_event->key.keysym.sym);
        } catch (std::out_of_range err) {
            fprintf(stderr, "No matching key %d.\n", sdl_event->key.keysym.sym);
        }
        break;
    case SDL_MOUSEMOTION:
        type = Event::MOUSE_MOTION;
        break;
    case SDL_MOUSEBUTTONDOWN:
        switch(sdl_event->button.button) {
        case SDL_BUTTON_LEFT:
            type = Event::MOUSE_LEFT_CLICK;
            break;
        case SDL_BUTTON_RIGHT:
            type = Event::MOUSE_RIGHT_CLICK;
            break;
        case SDL_BUTTON_MIDDLE:
            type = Event::MOUSE_MIDDLE_CLICK;
            break;
        }
        break;
    case SDL_MOUSEBUTTONUP:
        switch(sdl_event->button.button) {
        case SDL_BUTTON_LEFT:
            type = Event::MOUSE_LEFT_RELEASE;
            break;
        case SDL_BUTTON_RIGHT:
            type = Event::MOUSE_RIGHT_RELEASE;
            break;
        case SDL_BUTTON_MIDDLE:
            type = Event::MOUSE_MIDDLE_RELEASE;
            break;
        }
        break;
    case SDL_QUIT:
        type = Event::QUIT;
        break;
        // case SDL_WINDOWEVENT:
        //     //EMPTY
        //     break;
        // case SDL_TEXTINPUT:
        //     //EMPTY
        //     break;
        // case SDL_SYSWMEVENT:
        //     //EMPTY
        //     break;
    default:
        fprintf(stderr, "Unhandled sdl_event: %d.\n", sdl_event->type);
        break;
    }

    if (type == Event::NONE
        || events::event_fact_map.find(type) == events::event_fact_map.end()) {
        fprintf(stderr, "Events::convert_sdl_events: \
No available event factory for event %d.\n", type);
        return NULL;
    }

    return events::event_fact_map.at(type)();
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


void events::fill_defaults()
{
    typedef std::pair<Event::Event_Type, Event *(*)()> event_pair;
    typedef std::pair<SDL_Keycode, Event::Event_Type> key_pair;

    key_dwn_map.insert(key_pair(SDLK_q, Event::QUIT));
    key_dwn_map.insert(key_pair(SDLK_RIGHT, Event::START_MOVE_EAST));
    key_dwn_map.insert(key_pair(SDLK_UP, Event::START_MOVE_NORTH));
    key_dwn_map.insert(key_pair(SDLK_LEFT, Event::START_MOVE_WEST));
    key_dwn_map.insert(key_pair(SDLK_DOWN, Event::START_MOVE_SOUTH));

    key_up_map.insert(key_pair(SDLK_RIGHT, Event::END_MOVE_EAST));
    key_up_map.insert(key_pair(SDLK_UP, Event::END_MOVE_NORTH));
    key_up_map.insert(key_pair(SDLK_LEFT, Event::END_MOVE_WEST));
    key_up_map.insert(key_pair(SDLK_DOWN, Event::END_MOVE_SOUTH));

    event_fact_map.insert(event_pair(Event::QUIT, create_event<QuitEvent>));
    event_fact_map.insert(event_pair(Event::START_MOVE_EAST,
                                     create_dir_event<MoveEvent, EAST>));
    event_fact_map.insert(event_pair(Event::START_MOVE_NORTH,
                                     create_dir_event<MoveEvent, NORTH>));
    event_fact_map.insert(event_pair(Event::START_MOVE_WEST,
                                     create_dir_event<MoveEvent, WEST>));
    event_fact_map.insert(event_pair(Event::START_MOVE_SOUTH,
                                     create_dir_event<MoveEvent, SOUTH>));
    event_fact_map.insert(event_pair(Event::END_MOVE_EAST,
                                     create_dir_event<StopMoveEvent, EAST>));
    event_fact_map.insert(event_pair(Event::END_MOVE_NORTH,
                                     create_dir_event<StopMoveEvent, NORTH>));
    event_fact_map.insert(event_pair(Event::END_MOVE_WEST,
                                     create_dir_event<StopMoveEvent, WEST>));
    event_fact_map.insert(event_pair(Event::END_MOVE_SOUTH,
                                     create_dir_event<StopMoveEvent, SOUTH>));
}
