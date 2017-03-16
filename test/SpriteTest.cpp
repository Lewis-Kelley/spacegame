#include "gtest/gtest.h"

#include "MockRenderer.hpp"
#include "../src/drawables/Sprite.hpp"

class ExposedSprite : public Sprite {
public:
    ExposedSprite(SDL_Rect src_rect, SDL_Rect dest_rect,
                  SDL_Texture *tex)
        : Sprite(src_rect, dest_rect, tex) { }
    ExposedSprite(SDL_Rect rect, SDL_Texture *tex, bool dest)
        : Sprite(rect, tex, dest) { }
    ExposedSprite(SDL_Texture *tex)
        : Sprite(tex) { }

    double get_draw_x() { return Sprite::get_draw_x(); }
    double get_draw_y() { return Sprite::get_draw_y(); }
    double get_width() { return Sprite::get_width(); }
    double get_height() { return Sprite::get_height(); }
    void set_draw_x(double x) { Sprite::set_draw_x(x); }
    void set_draw_y(double y) { Sprite::set_draw_y(y); }
    void set_width(double width) { Sprite::set_width(width); }
    void set_height(double height) { Sprite::set_height(height); }
};

TEST(SpriteTest, ConstructorTexture) {
    window::init(0, 0);
    SDL_Texture *tex = window::rend
        ->load_texture("/home/lewis/programs/spacegame/assets/red_ship.png");
    ExposedSprite tested(tex);

    ASSERT_EQ(0, tested.get_draw_x());
    ASSERT_EQ(0, tested.get_draw_y());
    ASSERT_EQ(0, tested.get_width());
    ASSERT_EQ(0, tested.get_height());
}

TEST(SpriteTest, DrawNullTexture) {
    MockRenderer rend;
    ExposedSprite tested(NULL);

    EXPECT_CALL(rend, render_copy(testing::_, testing::_, testing::_));
    ASSERT_FALSE(tested.draw(&rend));
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
