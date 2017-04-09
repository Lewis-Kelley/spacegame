#include "Window.hpp"

Window *Window::self = nullptr;

Window *Window::get_instance()
{
    if (self == nullptr) {
        self = new Window(INIT_WIDTH, INIT_HEIGHT);
    }

    return self;
}

/**
 * Initializes SDL using the default values for width and height.
 *
 * @return true if success, false if there was an error.
 */
void Window::init()
{
    init_sdl_video();
    init_sdl_image();

    wind = create_window();
    rend = create_renderer();
}

void Window::init_sdl_video()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        throw SDL_GetError();
    }
}

void Window::init_sdl_image()
{
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        throw SDL_GetError();
    }
}

SDL_Window *Window::create_window()
{
    SDL_Window *window;
    window
        = SDL_CreateWindow("spacegame", SDL_WINDOWPOS_UNDEFINED,
                           SDL_WINDOWPOS_UNDEFINED, width, height,
                           SDL_WINDOW_SHOWN);
    if (window == nullptr) {
        throw SDL_GetError();
    }

    return window;
}

Renderer *Window::create_renderer()
{
    return new Renderer(wind);
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
    if (prev_time == -1) {
        throw NoPreviousTimeException();
    }

    return SDL_GetTicks() - prev_time;
}
