#include <stdio.h>
#include <SDL2/SDL.h>
#include <string>
#include <vector>
#include <queue>

#include "listeners/CameraListener.hpp"
#include "events/EventHandler.hpp"
#include "events/Events.hpp"
#include "entities/Fighter.hpp"
#include "util/GameState.hpp"
#include "listeners/MovementListener.hpp"
#include "events/QuitEvent.hpp"
#include "listeners/QuitListener.hpp"
#include "drawables/Rectangle.hpp"
#include "drawables/Sprite.hpp"
#include "listeners/SwitchListener.hpp"
#include "tiles/TileMap.hpp"
#include "util/Window.hpp"

void add_unit(std::vector<Drawable *> *drawings, std::queue<Unit *> *units,
              Unit *unit)
{
    drawings->push_back(unit);
    units->push(unit);
}

void add_tile_rects(std::vector<Rectangle *> rects)
{
    for (std::vector<Rectangle *>::iterator it = rects.begin();
         it != rects.end(); it++) {
        gamestate::drawings.push_back(*it);
    }
}

Fighter *init_fighter(TileMap *tile_map, int row, int col, SDL_Texture *tex,
                      std::string team_name)
{
    Fighter *fighter = new Fighter(gamestate::tile_size, tile_map, row, col,
                                   new Sprite(tex));
    fighter->set_team_name(team_name);

    return fighter;
}

#ifndef TESTING
int main(int argc, char *argv[])
{
    window::init();
    std::queue<Unit *> units;
    MovementListener movProx;

    TileMap tile_map(10, 10);
    add_tile_rects(tile_map.get_tile_rects());
    Fighter *red_fighter = NULL;
    Fighter *blue_fighter = NULL;
    SDL_Texture *red_ship_tex
        = window::rend->
        load_texture("/home/lewis/programs/spacegame/assets/red_ship.png");
    SDL_Texture *blue_ship_tex
        = window::rend->
        load_texture("/home/lewis/programs/spacegame/assets/blue_ship.png");
    try {
        red_fighter = init_fighter(&tile_map, 0, 0, red_ship_tex, "Enemies");
        blue_fighter = init_fighter(&tile_map, 2, 1, blue_ship_tex, "Allies");
        add_unit(&gamestate::drawings, &units, red_fighter);
        add_unit(&gamestate::drawings, &units, blue_fighter);
    } catch (char const* err) {
        fprintf(stderr, "ERROR: %s\n", err);
    }

    QuitListener ql;
    SwitchListener sl(&units);
    CameraListener cl(&gamestate::drawings);

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
#endif
