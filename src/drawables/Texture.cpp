#include "Texture.hpp"

Texture::Texture() : tex(NULL) { }

Texture::Texture(Texture *tex)
{
    if (tex != NULL) {
        this->tex = tex->tex;
    } else {
        this->tex = NULL;
    }
}

Texture::Texture(SDL_Texture *tex) : tex(tex) { }

Texture::Texture(Renderer *rend, std::string filename)
    : Texture(rend->load_texture(filename)) { }
