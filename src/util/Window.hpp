#ifndef WINDOW_H
#define WINDOW_H

#define INIT_WIDTH 500
#define INIT_HEIGHT 500

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "../drawables/Renderer.hpp"

namespace window {
    extern double prev_time;
    extern SDL_Window *wind;
    extern Renderer *rend;
    extern short width;
    extern short height;

    bool init();
    bool init(short width, short height);
    void free();
    void clear_render();
    void present_render();
    double get_delta();
}

#endif /* WINDOW_H */
