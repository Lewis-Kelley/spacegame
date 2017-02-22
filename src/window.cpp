#include "window.hpp"

window *window::self;

window::window() {
    init();
}

/**
 * @return A pointer to the global window instance.
 */
window *window::get_instance() {
    if (window::self == NULL) {
        window::self = new window();
    }

    return window::self;
}

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
 * @param width The initial width of the window.
 * @param height The initial height of the window.
 * @return true if success, false if there was an error.
 */
bool window::init(short width, short height)
{
    free();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL failed to initialize.\nSDL error: %s.\n", SDL_GetError());
        return false;
    }

    wind = SDL_CreateWindow("space-armada",
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            width, height, SDL_WINDOW_SHOWN);
    if (wind == NULL) {
        printf("Window could not be created.\nSDL error: %s.\n",
               SDL_GetError());
        width = 0;
        height = 0;
        return false;
    }

    rend = SDL_CreateRenderer(wind, -1, SDL_RENDERER_ACCELERATED
                              | SDL_RENDERER_PRESENTVSYNC);

    if (rend == NULL) {
        printf("Renderer could not be created.\nSDL error: %s.\n",
               SDL_GetError());
        return false;
    }

    // Set default color
    SDL_SetRenderDrawColor(rend, 0xFF, 0xFF, 0xFF, 0xFF);
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        printf("SDL_image could not initialize.\nSDL_image error: %s.\n",
               IMG_GetError());
        return false;
    }

    return true;
}

/**
 * Free all the memory used by the SDL window and renderer, as well as
 * quit all the SDL processes.
 */
void window::free()
{
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(wind);
    IMG_Quit();
    SDL_Quit();
}
