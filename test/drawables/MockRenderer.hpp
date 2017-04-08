#include <gmock/gmock.h>
#include "../../src/drawables/Renderer.hpp"

class MockRenderer : public Renderer {
 public:
    MockRenderer() : Renderer(NULL) { }

    MOCK_METHOD3(render_copy, bool(Texture *tex, SDL_Rect *src_rect,
                                   SDL_Rect *dest_rect));
    MOCK_METHOD0(present, void());
};
