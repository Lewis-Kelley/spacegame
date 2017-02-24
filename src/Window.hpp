#ifndef WINDOW_H
#define WINDOW_H

#define INIT_WIDTH 500
#define INIT_HEIGHT 500

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * Singleton class holding all the information about the physical
 * Window itself, including the SDL instances of the renderer and
 * Window.
 */
class Window {
private:
    static Window *self;
    double prev_time;
    SDL_Window *wind;
    SDL_Renderer *rend;
    short width;
    short height;
    Window();
public:
    static Window *get_instance();
    bool init();
    bool init(short width, short height);
    void free();

    /**
     * @return The SDL_Window for the game.
     */
    SDL_Window *get_window() { return wind; }

    /**
     * @return The SDL_Renderer for the game.
     */
    SDL_Renderer *get_renderer() { return rend; }

    /**
     * Clears the renderer for a new buffer to be drawn.
     */
    void clear_render() { SDL_RenderClear(rend); }

    /**
     * Draws whatever has been held in the renderer to the screen.
     */
    void present_render() {
        prev_time = SDL_GetTicks();
        SDL_RenderPresent(rend);
    }

    /**
     * Return the delta time since last the previous render.
     */
    double get_delta() { return SDL_GetTicks() - prev_time; }
};

#endif /* WINDOW_H */
