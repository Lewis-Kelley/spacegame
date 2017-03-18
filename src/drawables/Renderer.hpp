#ifndef RENDERER_H
#define RENDERER_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>

#include "Texture.hpp"

/**
 * Wrapper class for SDL_Renderer.
 */
class Renderer {
private:
    SDL_Renderer *rend;
public:
    /**
     * Wrap a new Renderer around the passsed SDL_Renderer.
     *
     * @param rend The SDL_Renderer to be used by this Renderer.
     */
    Renderer(SDL_Renderer *rend) : rend(rend) { }
    virtual ~Renderer();

    /**
     * Clears the render in preparation for a new frame.
     */
    void clear() { SDL_RenderClear(rend); }

    /**
     * Presents the loaded frame to the screen.
     */
    void present() { SDL_RenderPresent(rend); }

    bool render_copy(Texture *tex, SDL_Rect *src_rect,
                             SDL_Rect *dest_rect);
    bool fill_rect(SDL_Rect *dest_rect, SDL_Color *color);
    Texture *load_texture(std::string filename);
};

#endif /* RENDERER_H */
