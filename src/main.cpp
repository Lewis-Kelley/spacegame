#include <stdio.h>
#include <SDL2/SDL.h>

#include "window.hpp"
#include "event_handler.hpp"

bool cont = true;

int main(int argc, char *argv[])
{
    window *wind = window::get_instance();

    SDL_Event event;
    double curr_time;
    double last_time = SDL_GetTicks();

    while (cont) {
        wind->clear_render();

        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                cont = false;
            } else {
                event_handler::handle_event(&event);
            }
        }
        curr_time = SDL_GetTicks();
        last_time = curr_time;
        wind->present_render();
    }

    return 0;
}
