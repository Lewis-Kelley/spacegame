#include "Renderer.hpp"

Renderer::Renderer(SDL_Window *wind)
{
    rend = SDL_CreateRenderer(wind, -1, SDL_RENDERER_ACCELERATED
                              | SDL_RENDERER_PRESENTVSYNC);

    if (rend == NULL) {
        throw SDL_GetError();
    }

    SDL_SetRenderDrawColor(rend, 0x00, 0x00, 0x00, 0xFF);
}

Renderer::~Renderer()
{
    SDL_DestroyRenderer(rend);
}

/**
 * Draws the passed texture to the frame.
 *
 * @param tex The Texture to draw.
 * @param src_rect The rectangle defining what portion of tex to draw.
 * NULL means to draw the whole texture.
 * @param dest_rect The rectangle defining where to draw text on the frame.
 * NULL means to fill the whole frame.
 * @return True if successful, false otherwise.
 */
bool Renderer::render_copy(Texture *tex, SDL_Rect *src_rect,
                           SDL_Rect *dest_rect)
{
    return tex != NULL && tex->get_sdl_tex() != NULL
        && SDL_RenderCopy(rend, tex->get_sdl_tex(), src_rect, dest_rect);
}

/**
 * Fills the passed rectangle with the given color.
 *
 * @param dest_rect The rectangle of where to draw onscreen.
 * @param color The color to fill in the rectangle with.
 * @return true if successful, false otherwise.
 */
bool Renderer::fill_rect(SDL_Rect *dest_rect, SDL_Color *color)
{
    SDL_Color hold;
    bool status;

    SDL_GetRenderDrawColor(rend, &hold.r, &hold.g, &hold.b, &hold.a);
    SDL_SetRenderDrawColor(rend, color->r, color->g, color->b, color->a);
    status = SDL_RenderFillRect(rend, dest_rect);
    SDL_SetRenderDrawColor(rend, hold.r, hold.g, hold.b, hold.a);

    return status;
}

/**
 * Load the texture in the file located at the filename.
 *
 * @param filename The path to the image file.
 * @return A new Texture based of the image file.
 */
Texture *Renderer::load_texture(std::string filename) {
    SDL_Texture *tex = NULL;
    SDL_Surface *surf = IMG_Load(filename.c_str());

    if (surf == NULL) {
        throw IMG_GetError();
    }

    // Set invisible color
    SDL_SetColorKey(surf, SDL_TRUE, SDL_MapRGB(surf->format, 0xFF, 0x00, 0xFF));
    // Create texture from the surface
    tex = SDL_CreateTextureFromSurface(rend, surf);

    if (tex == NULL) {
        throw IMG_GetError();
    }

    return new Texture(tex);
}
