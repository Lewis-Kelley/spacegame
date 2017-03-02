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
#include "MovementListener.hpp"

void add_unit(std::vector<Drawable *> *drawings, std::queue<Unit *> *units,
              Unit *unit)
{
    drawings->push_back(unit);
    units->push(unit);
}

int main(int argc, char *argv[])
{
    window::init();
    std::queue<Unit *> units;
    MovementListener movProx;

    TileMap tile_map(10, 10);
    Fighter *red_fighter = NULL;
    Fighter *other_fighter = NULL;
    SDL_Texture *red_ship_tex
        = Sprite::
        load_texture("/home/lewis/programs/spacegame/assets/red_ship.png");
    SDL_Texture *blue_ship_tex
        = Sprite::
        load_texture("/home/lewis/programs/spacegame/assets/blue_ship.png");
    try {
        red_fighter = new Fighter(50, &tile_map, 0, 0, new Sprite(red_ship_tex));
        red_fighter->set_team_name("Allies");
        other_fighter = new Fighter(50, &tile_map, 2, 1, new Sprite(blue_ship_tex));
        other_fighter->set_team_name("Allies");
        add_unit(&gamestate::drawings, &units, red_fighter);
        add_unit(&gamestate::drawings, &units, other_fighter);
    } catch (char const* err) {
        fprintf(stderr, "ERROR: %s\n", err);
    }

    QuitListener ql;
    SwitchListener sl(&units);

    events::fill_defaults();
    events::event_queue.push(new TriggerSwitchEvent()); // Select the first Unit

    SDL_Event sdl_event;
    Event *event;
    double delta;

    gamestate::running = true;
    while (gamestate::running) {
        window::clear_render();

        while (SDL_PollEvent(&sdl_event) != 0) {
            event = events::convert_SDL_Event(&sdl_event);
            if (event != NULL) {
                events::event_queue.push(event);
            }
        }

        while (events::event_queue.size() > 0) {
            event_handler::handle_event(events::event_queue.front());
            events::event_queue.pop();
        }

        delta = window::get_delta();
        gamestate::draw_all(delta);
        window::present_render();
    }

    if (red_fighter != NULL) {
        delete red_fighter;
    }

    SDL_DestroyTexture(red_ship_tex);
    SDL_DestroyTexture(blue_ship_tex);
    window::free();

    return 0;
}
