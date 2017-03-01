#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <queue>

#include "TileMap.hpp"
#include "QuitListener.hpp"
#include "Window.hpp"
#include "EventHandler.hpp"
#include "Fighter.hpp"
#include "Sprite.hpp"
#include "GameState.hpp"
#include "Events.hpp"
#include "QuitEvent.hpp"
#include "SwitchListener.hpp"

bool cont = true;

Event *create_quit_event()
{
    return new QuitEvent();
}

int main(int argc, char *argv[])
{
    Window *wind = Window::get_instance();
    EventHandler *handler = EventHandler::get_instance();
    std::vector<Drawable *> drawings;
    std::queue<Unit *> units;

    TileMap tile_map(10, 10);
    Sprite *fighter_sprite = NULL;
    Sprite *other_sprite = NULL;
    Fighter *red_fighter = NULL;
    Fighter *other_fighter = NULL;
    try {
        fighter_sprite
            = new Sprite((SDL_Rect){0, 0, 50, 50},
                         "/home/lewis/programs/spacegame/assets/red_ship.png",
                         true);
        other_sprite
            = new Sprite((SDL_Rect){50, 100, 50, 50},
                         "/home/lewis/programs/spacegame/assets/red_ship.png",
                         true);
        red_fighter = new Fighter(tile_map.at(0, 0), fighter_sprite);
        red_fighter->set_team_name("Allies");
        other_fighter = new Fighter(tile_map.at(2, 1), other_sprite);
        other_fighter->set_team_name("Enemies");
        handler->add_listener(Event::START_UNIT_MOVE, red_fighter);
        handler->add_listener(Event::END_UNIT_MOVE, red_fighter);
        handler->add_listener(Event::UNIT_MOVE_FINISHED, red_fighter);
        handler->add_listener(Event::START_CAMERA_MOVE, red_fighter);
        handler->add_listener(Event::START_CAMERA_MOVE, other_fighter);
        handler->add_listener(Event::STOP_CAMERA_MOVE, red_fighter);
        handler->add_listener(Event::STOP_CAMERA_MOVE, other_fighter);
        handler->add_listener(Event::SWITCH_UNITS, red_fighter);
        handler->add_listener(Event::SWITCH_UNITS, other_fighter);
        drawings.push_back(red_fighter);
        drawings.push_back(other_fighter);
        units.push(red_fighter);
        units.push(other_fighter);
    } catch (char const* err) {
        fprintf(stderr, "ERROR: %s\n", err);
    }

    handler->add_listener(Event::QUIT, new QuitListener());
    handler->add_listener(Event::TRIGGER_SWITCH, new SwitchListener(&units));

    events::fill_defaults();

    SDL_Event sdl_event;
    Event *event;
    double delta;

    gamestate::running = true;
    while (gamestate::running) {
        wind->clear_render();

        while (SDL_PollEvent(&sdl_event) != 0) {
            event = events::convert_SDL_Event(&sdl_event);
            if (event != NULL) {
                events::event_queue.push(event);
            }
        }

        while (events::event_queue.size() > 0) {
            handler->handle_event(events::event_queue.front());
            events::event_queue.pop();
        }

        delta = wind->get_delta();
        for (int i = 0; i < (int)drawings.size(); i++) {
            drawings.at(i)->update(delta);
            drawings.at(i)->draw();
        }
        wind->present_render();
    }

    if (red_fighter != NULL) {
        delete red_fighter;
    }

    if (fighter_sprite != NULL) {
        delete fighter_sprite;
    }

    return 0;
}
