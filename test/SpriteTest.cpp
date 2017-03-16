#include <gtest/gtest.h>
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
    ExposedSprite(SDL_Rect src_rect, SDL_Rect dest_rect,
                  std::string filename)
        : Sprite(src_rect, dest_rect, filename) { }
    ExposedSprite(SDL_Rect rect, std::string filename, bool dest)
        : Sprite(rect, filename, dest) { }
    ExposedSprite(std::string filename) : Sprite(filename) { }

    double get_draw_x() { return Sprite::get_draw_x(); }
    double get_draw_y() { return Sprite::get_draw_y(); }
    double get_width() { return Sprite::get_width(); }
    double get_height() { return Sprite::get_height(); }
    void set_draw_x(double x) { Sprite::set_draw_x(x); }
    void set_draw_y(double y) { Sprite::set_draw_y(y); }
    void set_width(double width) { Sprite::set_width(width); }
    void set_height(double height) { Sprite::set_height(height); }
};

TEST(MySpriteTest, ConstructorFilename) {
    window::init(0, 0);
    ExposedSprite tested("/home/lewis/programs/spacegame/assets/red_ship.png");

    EXPECT_EQ(0, tested.get_draw_x());
}


#ifdef TESTING
int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif
