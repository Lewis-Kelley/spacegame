#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "QuitListener.hpp"
#include "Window.hpp"
#include "EventHandler.hpp"
#include "Fighter.hpp"
#include "Sprite.hpp"
#include "GameState.hpp"
#include "Events.hpp"
#include "QuitEvent.hpp"

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

    Tile *tile = NULL;
    Sprite *fighter_sprite = NULL;
    Fighter *red_fighter = NULL;
    try {
        tile = new Tile(0, 0);
        tile->add_neighbor(EAST, new Tile(0, 1));
        fighter_sprite
            = new Sprite((SDL_Rect){0, 0, 50, 50},
                         "/home/lewis/programs/spacegame/assets/red_ship.png",
                         true);
        red_fighter = new Fighter(tile, fighter_sprite);
        handler->add_listener(Event::START_MOVE_EAST, red_fighter);
        handler->add_listener(Event::START_MOVE_NORTH, red_fighter);
        handler->add_listener(Event::START_MOVE_WEST, red_fighter);
        handler->add_listener(Event::START_MOVE_SOUTH, red_fighter);
        drawings.push_back(red_fighter);
    } catch (char const* err) {
        fprintf(stderr, "ERROR: %s\n", err);
    }

    handler->add_listener(Event::QUIT, new QuitListener());

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
