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
    double prev_time;
    SDL_Window *wind;
    Renderer *rend;
    uint16_t width;
    uint16_t height;

 protected:
    static Window *self;

    Window(uint16_t width, uint16_t height)
        : prev_time(-1), wind(nullptr), rend(nullptr),
          width(width), height(height) { }

    virtual void init_sdl_video();
    virtual void init_sdl_image();
    virtual SDL_Window *create_window();
    virtual Renderer *create_renderer();

 public:
    class NoPreviousTimeException : public std::exception {
        virtual const char* what() const throw()
        {
            return "Delta cannot be found without a previous render time.\n";
        }
    };

    static Window *get_instance();
    void init();

    virtual ~Window();

    SDL_Window *get_wind() { return wind; }
    Renderer *get_rend() { return rend; }

    uint16_t get_width() { return width; }
    uint16_t get_height() { return height; }

    double get_delta();

    void clear_render();
    void present_render();
};

#endif /* WINDOW_H */
