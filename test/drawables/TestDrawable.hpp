#ifndef DRAWABLETEST_H
#define DRAWABLETEST_H

#include <gtest/gtest.h>

#include "../../src/drawables/Drawable.hpp"

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
    if (int_cast) val = static_cast<int>(val);
    ASSERT_DOUBLE_EQ(val, (tested->*get_func)());

    val = 1.0;
    (tested->*set_func)(val);
    if (int_cast) val = static_cast<int>(val);
    ASSERT_DOUBLE_EQ(val, (tested->*get_func)());

    val = -1.0;
    (tested->*set_func)(val);
    if (int_cast) val = static_cast<int>(val);
    ASSERT_DOUBLE_EQ(val, (tested->*get_func)());

    val = 106.89;
    (tested->*set_func)(val);
    if (int_cast) val = static_cast<int>(val);
    ASSERT_DOUBLE_EQ(val, (tested->*get_func)());
}

static void test_movement(Drawable *tested, Movement move)
{
    double tracked_x = tested->get_draw_x();
    double tracked_y = tested->get_draw_y();

    tested->move(move.dx, move.dy);

    tracked_x += move.dx;
    tracked_y += move.dy;

    ASSERT_EQ(tracked_x, tested->get_draw_x());
    ASSERT_EQ(tracked_y, tested->get_draw_y());
}

void ASSERT_MOVE(Drawable *tested)
{
    Movement move;

    move.dx = 1.5;
    move.dy = 2.5;
    test_movement(tested, move);

    move.dx = 0.0;
    move.dy = 0.0;
    test_movement(tested, move);

    move.dx = -1.5;
    move.dy = -2.5;
    test_movement(tested, move);
}

void ASSERT_START_MOVE(Drawable *tested)
{
    SDL_Rect dim;
    Movement move;
    double time;

    dim.x = tested->get_draw_x();
    dim.y = tested->get_draw_y();
    dim.w = tested->get_width();
    dim.h = tested->get_height();

    move.dx = 0.0;
    move.dy = 0.0;

    time = 1.0;

    tested->start_move(&move, CAMERA_X);

    tested->update(time);
    dim.x += move.dx * time;
    dim.y += move.dy * time;

    ASSERT_DIMENSIONS(tested, dim);
}

#endif /* DRAWABLETEST_H */
