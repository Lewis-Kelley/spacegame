#include "Window.hpp"

double window::prev_time;
SDL_Window *window::wind;
SDL_Renderer *window::rend;
short window::width;
short window::height;

/**
 * Initializes SDL using the default values for width and height.
 *
 * @return true if success, false if there was an error.
 */
bool window::init()
{
    return init(INIT_WIDTH, INIT_HEIGHT);
}

/**
 * Initializes SDL using the passed values for width and height.
 *
 * @param width The initial width of the Window.
 * @param height The initial height of the Window.
 * @return true if success, false if there was an error.
 */
bool window::init(short width, short height)
{
    free();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDL_GetError();
    }

    wind = SDL_CreateWindow("spacegame",
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            width, height, SDL_WINDOW_SHOWN);
    if (wind == NULL) {
        throw SDL_GetError();
    }

    rend = SDL_CreateRenderer(wind, -1, SDL_RENDERER_ACCELERATED
                              | SDL_RENDERER_PRESENTVSYNC);

    if (rend == NULL) {
        throw SDL_GetError();
    }

    // Set default color
    SDL_SetRenderDrawColor(rend, 0x00, 0x00, 0x00, 0xFF);
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        throw SDL_GetError();
    }

    return true;
}

/**
 * Free all the memory used by the SDL Window and renderer, as well as
 * quit all the SDL processes.
 */
void window::free()
{
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(wind);
    IMG_Quit();
    SDL_Quit();
}

/**
 * Clears the renderer for a new buffer to be drawn.
 */
void window::clear_render()
{
    SDL_RenderClear(rend);
}

/**
 * Draws whatever has been held in the renderer to the screen.
 */
void window::present_render()
{
    prev_time = SDL_GetTicks();
    SDL_RenderPresent(rend);
}

/**
 * Return the delta time since last the previous render.
 */
double window::get_delta()
{
    return SDL_GetTicks() - prev_time;
}
