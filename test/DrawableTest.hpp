#ifndef DRAWABLETEST_H
#define DRAWABLETEST_H

#include <gtest/gtest.h>

#include "../src/drawables/Drawable.hpp"

void ASSERT_DIMENSIONS(Drawable *tested, double x, double y, double w, double h)
{
    ASSERT_DOUBLE_EQ(x, tested->get_draw_x());
    ASSERT_DOUBLE_EQ(y, tested->get_draw_y());
    ASSERT_DOUBLE_EQ(w, tested->get_width());
    ASSERT_DOUBLE_EQ(h, tested->get_height());
}

void ASSERT_DIMENSIONS(Drawable *tested, SDL_Rect dim)
{
    ASSERT_DIMENSIONS(tested, dim.x, dim.y, dim.w, dim.h);
}

void ASSERT_SET_GET_DIM(Drawable *tested, double (Drawable::*get_func)(),
                        void (Drawable::*set_func)(double), bool int_cast)
{
    double val = 0.0;
    (tested->*set_func)(val);
    if (int_cast) val = (int)val;
    ASSERT_DOUBLE_EQ(val, (tested->*get_func)());

    val = 1.0;
    (tested->*set_func)(val);
    if (int_cast) val = (int)val;
    ASSERT_DOUBLE_EQ(val, (tested->*get_func)());

    val = -1.0;
    (tested->*set_func)(val);
    if (int_cast) val = (int)val;
    ASSERT_DOUBLE_EQ(val, (tested->*get_func)());

    val = 106.89;
    (tested->*set_func)(val);
    if (int_cast) val = (int)val;
    ASSERT_DOUBLE_EQ(val, (tested->*get_func)());
}

#endif /* DRAWABLETEST_H */
