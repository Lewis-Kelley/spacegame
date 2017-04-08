#include <string>

#include <gmock/gmock.h>
#include "../../src/drawables/Texture.hpp"

class MockTexture : public Texture {
 public:
    MockTexture() : Texture(static_cast<SDL_Texture *>(NULL)) { }
    explicit MockTexture(SDL_Texture *tex) : Texture(tex) { }
    MockTexture(Renderer *rend, std::string filename)
        : Texture(rend, filename) { }

    MOCK_METHOD0(get_sdl_tex, SDL_Texture*());
};
