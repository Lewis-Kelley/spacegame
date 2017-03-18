#include "Texture.hpp"

bool operator==(const SDL_Rect &lhs, const SDL_Rect &rhs)
{
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.w == rhs.w && lhs.h == rhs.h;
}

Texture::Texture(Texture *other)
{
    if (other != NULL) {
        tex = other->get_sdl_tex();
    } else {
        throw "Trying to clone a NULL Texture.";
    }
}

Texture::Texture(SDL_Texture *tex) : tex(tex) { }

Texture::Texture(Renderer *rend, std::string filename)
{
    Texture *other = rend->load_texture(filename);
    tex = other->get_sdl_tex();
}
