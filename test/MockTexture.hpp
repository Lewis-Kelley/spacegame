#include "gmock/gmock.h"
#include "../src/drawables/Texture.hpp"

class MockTexture : public Texture {
public:
    MockTexture() : Texture((SDL_Texture *)NULL) { }
    MockTexture(SDL_Texture *tex) : Texture(tex) { }
    MockTexture(Renderer *rend, std::string filename)
        : Texture(rend, filename) { }

    MOCK_METHOD0(get_sdl_tex, SDL_Texture*());
};
