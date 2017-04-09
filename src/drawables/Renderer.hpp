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

 protected:
    Renderer() : rend(NULL) { }

 public:
    explicit Renderer(SDL_Window *wind);

    virtual ~Renderer();

    /**
     * Clears the render in preparation for a new frame.
     */
    virtual void clear() { SDL_RenderClear(rend); }

    /**
     * Presents the loaded frame to the screen.
     */
    virtual void present() { SDL_RenderPresent(rend); }

    virtual bool render_copy(Texture *tex, SDL_Rect *src_rect,
                             SDL_Rect *dest_rect);
    virtual bool fill_rect(SDL_Rect *dest_rect, SDL_Color *color);
    virtual Texture *load_texture(std::string filename);
};

#endif /* RENDERER_H */
