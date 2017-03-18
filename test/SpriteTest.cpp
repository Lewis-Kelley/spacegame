#include <gtest/gtest.h>

#include "../src/drawables/Sprite.hpp"
#include "DrawableTest.hpp"
#include "MockRenderer.hpp"
#include "MockTexture.hpp"

using namespace testing;

TEST(SpriteTest, ConstructorTexture)
{
    MockTexture tex;
    Sprite tested(&tex);

    ASSERT_DIMENSIONS(&tested, 0, 0, 0, 0);
}

TEST(SpriteTest, ConstructorSrcAndDestZeros)
{
    MockTexture tex;
    SDL_Rect src = (SDL_Rect){0, 0, 0, 0};
    SDL_Rect dest = (SDL_Rect){0, 0, 0, 0};
    Sprite tested(src, dest, &tex);

    ASSERT_DIMENSIONS(&tested, 0, 0, 0, 0);
}

TEST(SpriteTest, ConstructorSrcAndDestVals)
{
    MockTexture tex;
    SDL_Rect src = (SDL_Rect){5, 10, 2, 5};
    SDL_Rect dest = (SDL_Rect){4, 8, 1, 9};
    Sprite tested(src, dest, &tex);

    ASSERT_DIMENSIONS(&tested, dest);
}

TEST(SpriteTest, SetDrawX)
{
    MockTexture tex;
    Sprite tested(&tex);

    ASSERT_SET_GET_DIM(&tested,
                       (double (Drawable::*)())&Sprite::get_draw_x,
                       (void (Drawable::*)(double))&Sprite::set_draw_x,
                       false);
}

TEST(SpriteTest, SetDrawY)
{
    MockTexture tex;
    Sprite tested(&tex);

    ASSERT_SET_GET_DIM(&tested,
                       (double (Drawable::*)())&Sprite::get_draw_y,
                       (void (Drawable::*)(double))&Sprite::set_draw_y,
                       false);
}

TEST(SpriteTest, SetWidth)
{
    MockTexture tex;
    Sprite tested(&tex);

    ASSERT_SET_GET_DIM(&tested,
                       (double (Drawable::*)())&Sprite::get_width,
                       (void (Drawable::*)(double))&Sprite::set_width,
                       true);
}

TEST(SpriteTest, SetHeight)
{
    MockTexture tex;
    Sprite tested(&tex);

    ASSERT_SET_GET_DIM(&tested,
                       (double (Drawable::*)())&Sprite::get_height,
                       (void (Drawable::*)(double))&Sprite::set_height,
                       true);
}

TEST(SpriteTest, DrawNullRenderer)
{
    MockTexture tex;
    Sprite tested(&tex);

    ASSERT_FALSE(tested.draw(NULL));
}

TEST(SpriteTest, DrawNullTexture)
{
    MockRenderer rend;
    Sprite tested(NULL);

    ASSERT_FALSE(tested.draw(&rend));
}

TEST(SpriteTest, DrawZeroTexture)
{
    MockTexture tex;
    MockRenderer rend;
    Sprite tested(&tex);

    EXPECT_CALL(rend, render_copy(&tex, _, _)).WillOnce(Return(true));

    ASSERT_TRUE(tested.draw(&rend));
}

TEST(SpriteTest, DrawActualTexture)
{
    MockTexture tex;
    MockRenderer rend;
    SDL_Rect src = (SDL_Rect){2, 2, 6, 9};
    SDL_Rect dest = (SDL_Rect){6, 8, 9, 3};
    Sprite tested(src, dest, &tex);

    EXPECT_CALL(rend, render_copy(&tex, Pointee(src), Pointee(dest)));

    tested.draw(&rend);
}

TEST(SpriteTest, UpdateDimensionsAndDraw)
{
    MockTexture tex;
    MockRenderer rend;
    SDL_Rect src = (SDL_Rect){2, 2, 6, 9};
    SDL_Rect dest = (SDL_Rect){6, 8, 9, 3};
    Sprite tested(src, dest, &tex);

    tested.set_draw_x(3);
    tested.set_width(4);
    dest.x = 3;
    dest.w = 4;

    EXPECT_CALL(rend, render_copy(&tex, Pointee(src), Pointee(dest)));
    tested.draw(&rend);

    tested.set_draw_y(3);
    tested.set_height(4);
    dest.y = 3;
    dest.h = 4;

    EXPECT_CALL(rend, render_copy(&tex, Pointee(src), Pointee(dest)));

    tested.draw(&rend);
}

int main(int argc, char *argv[])
{
    InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
