#ifndef TEXTURE_H
#define TEXTURE_H

#include <SDL2/SDL.h>
#include <string>

class Renderer;

class Texture {
private:
    SDL_Texture *tex;
public:
    Texture();
    Texture(Texture *tex);
    Texture(SDL_Texture *tex);
    Texture(Renderer *rend, std::string filename);

    SDL_Texture *get_sdl_tex() { return tex; }
};

#include "Renderer.hpp"

#endif /* TEXTURE_H */
