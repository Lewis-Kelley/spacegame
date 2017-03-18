#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <string>

class Renderer;

bool operator==(const SDL_Rect &lhs, const SDL_Rect &rhs);

/**
 * Adapter class for an SDL_Texture.
 */
class Texture {
private:
    SDL_Texture *tex;

    Texture(Texture *other);
public:
    /**
     * Create a new Texture from the given SDL_Texture.
     *
     * @param tex The SDL_Texture this Texture will wrap.
     */
    Texture(SDL_Texture *tex);

    /**
     * Create a new Texture from the given file using the passed
     * Renderer.
     *
     * @param rend The Renderer with which to load the file.
     * @param filename The path to the file to load.
     */
    Texture(Renderer *rend, std::string filename);

    /**
     * @return The underlying SDL_Texture
     */
    SDL_Texture *get_sdl_tex() { return tex; }
};

#include "Renderer.hpp"

#endif /* TEXTURE_H */
