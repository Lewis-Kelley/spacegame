#include "Window.hpp"

Window *Window::self;

Window::Window()
{
    init();
}

/**
 * @return A pointer to the global Window instance.
 */
Window *Window::get_instance()
{
    if (Window::self == NULL) {
        Window::self = new Window();
    }

    return Window::self;
}

/**
 * Initializes SDL using the default values for width and height.
 *
 * @return true if success, false if there was an error.
 */
bool Window::init()
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
bool Window::init(short width, short height)
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
void Window::free()
{
    SDL_DestroyRenderer(rend);
    SDL_DestroyWindow(wind);
    IMG_Quit();
    SDL_Quit();
}
