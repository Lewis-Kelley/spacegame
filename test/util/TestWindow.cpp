#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/util/Window.hpp"
#include "../drawables/MockRenderer.hpp"

class PMockWindow : public Window {
 public:
    PMockWindow() : Window(INIT_WIDTH, INIT_HEIGHT) { self = this; }

    MOCK_METHOD0(init_sdl_video, void());
    MOCK_METHOD0(init_sdl_image, void());
    MOCK_METHOD0(create_window, SDL_Window *());
    MOCK_METHOD0(create_renderer, Renderer *());
};

TEST(Init, CalledSDLInit)
{
    PMockWindow wind;

    EXPECT_CALL(wind, init_sdl_video()).Times(1);
    EXPECT_CALL(wind, init_sdl_image()).Times(1);
    EXPECT_CALL(wind, create_window()).Times(1)
        .WillOnce(testing::Return(nullptr));
    EXPECT_CALL(wind, create_renderer()).Times(1)
        .WillOnce(testing::Return(new MockRenderer()));

    wind.init();
}

TEST(GetDelta, NoPrevTime)
{
    PMockWindow wind;

    ASSERT_THROW(wind.get_delta(), Window::NoPreviousTimeException);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
