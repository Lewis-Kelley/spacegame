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
        GameState::get_instance()->drawings.push_back(*it);
    }
}

Fighter *init_fighter(TileMap *tile_map, int row, int col, Texture *tex,
                      std::string team_name)
{
    Fighter *fighter = new Fighter(GameState::get_instance()->tile_size,
                                   tile_map, row, col, new Sprite(tex));
    fighter->set_team_name(team_name);

    return fighter;
}

int main(int argc, char *argv[])
{
    Window *wind = Window::get_instance();
    wind->init();

    std::queue<Unit *> units;
    MovementListener movProx;

    auto state = GameState::get_instance();

    TileMap tile_map(10, 10);
    add_tile_rects(tile_map.get_tile_rects());
    Fighter *red_fighter = nullptr;
    Fighter *blue_fighter = nullptr;
    Texture *red_ship_tex = wind->get_rend()->
        load_texture("/home/lewis/programs/spacegame/assets/red_ship.png");
    Texture *blue_ship_tex = wind->get_rend()->
        load_texture("/home/lewis/programs/spacegame/assets/blue_ship.png");
    try {
        red_fighter = init_fighter(&tile_map, 0, 0, red_ship_tex, "Enemies");
        blue_fighter = init_fighter(&tile_map, 2, 1, blue_ship_tex, "Allies");
        add_unit(&state->drawings, &units, red_fighter);
        add_unit(&state->drawings, &units, blue_fighter);
    } catch (char const* err) {
        fprintf(stderr, "ERROR: %s\n", err);
    }

    QuitListener ql(state);
    ql.add_as_listener(EventHandler::get_instance());
    SwitchListener sl(&units);
    CameraListener cl(&state->drawings);

    events::fill_defaults();
    events::event_queue.push(new TriggerSwitchEvent());  // Select first Unit

    SDL_Event sdl_event;
    Event *event;
    double delta;
    auto handler = EventHandler::get_instance();

    state->set_is_running(true);

    while (state->get_is_running()) {
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
        state->draw_all(delta);
        wind->present_render();
    }

    if (red_fighter != nullptr) {
        delete red_fighter;
    }

    delete red_ship_tex;
    delete blue_ship_tex;

    delete wind;

    return 0;
}
