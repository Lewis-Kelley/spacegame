#ifndef WINDOW_H
#define WINDOW_H

#define INIT_WIDTH 500
#define INIT_HEIGHT 500

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdint.h>

#include "../drawables/Renderer.hpp"

class Window {
 private:
    static Window *self;

    double prev_time;
    SDL_Window *wind;
    Renderer *rend;
    uint16_t width;
    uint16_t height;

    Window() { }

 public:
    static void init();
    static void init(uint16_t width, uint16_t height);
    static Window *get_instance();

    ~Window();

    SDL_Window *get_wind() { return wind; }
    Renderer *get_rend() { return rend; }

    uint16_t get_width() { return width; }
    uint16_t get_height() { return height; }

    double get_delta();

    void clear_render();
    void present_render();
};

#endif /* WINDOW_H */
