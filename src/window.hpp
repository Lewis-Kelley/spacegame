#ifndef WINDOW_H
#define WINDOW_H

#define INIT_WIDTH 500
#define INIT_HEIGHT 500

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

/**
 * Singleton class holding all the information about the physical
 * window itself, including the SDL instances of the renderer and
 * window.
 */
class window {
private:
    static window *self;
    SDL_Window *wind;
    SDL_Renderer *rend;
    short width;
    short height;
    window();
public:
    static window *get_instance();
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
    void present_render() { SDL_RenderPresent(rend); }
};

#endif /* WINDOW_H */
