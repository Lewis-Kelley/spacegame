#include "Window.hpp"

Window *Window::self = nullptr;

/**
 * Initializes SDL using the default values for width and height.
 *
 * @return true if success, false if there was an error.
 */
void Window::init()
{
    init(INIT_WIDTH, INIT_HEIGHT);
}

/**
 * Initializes SDL using the passed values for width and height.
 *
 * @param width The initial width of the Window.
 * @param height The initial height of the Window.
 * @return true if success, false if there was an error.
 */
void Window::init(uint16_t width, uint16_t height)
{
    if (self != nullptr) {
        delete self;
    }

    self = new Window();

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDL_GetError();
    }

    self->wind = SDL_CreateWindow("spacegame",
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            width, height, SDL_WINDOW_SHOWN);
    if (self->wind == nullptr) {
        throw SDL_GetError();
    }

    SDL_Renderer *sdl_rend
        = SDL_CreateRenderer(self->wind, -1, SDL_RENDERER_ACCELERATED
                             | SDL_RENDERER_PRESENTVSYNC);

    if (sdl_rend == NULL) {
        throw SDL_GetError();
    }

    // Set default color
    SDL_SetRenderDrawColor(sdl_rend, 0x00, 0x00, 0x00, 0xFF);
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        throw SDL_GetError();
    }

    self->rend = new Renderer(sdl_rend);
}

Window *Window::get_instance()
{
    if (self == nullptr) {
        init();
    }

    return self;
}

/**
 * Free all the memory used by the SDL Window and renderer, as well as
 * quit all the SDL processes.
 */
Window::~Window()
{
    if (rend != NULL) {
        delete rend;
    }

    SDL_DestroyWindow(wind);
    IMG_Quit();
    SDL_Quit();
}

/**
 * Clears the renderer for a new buffer to be drawn.
 */
void Window::clear_render()
{
    rend->clear();
}

/**
 * Draws whatever has been held in the renderer to the screen.
 */
void Window::present_render()
{
    prev_time = SDL_GetTicks();
    rend->present();
}

/**
 * Return the delta time since last the previous render.
 */
double Window::get_delta()
{
    return SDL_GetTicks() - prev_time;
}
