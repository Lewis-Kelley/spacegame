#ifndef MOCKDRAWABLE_H
#define MOCKDRAWABLE_H

#include <gmock/gmock.h>

#include "../../src/drawables/Drawable.hpp"

class MockDrawable : public Drawable {
 public:
    MOCK_METHOD0(get_draw_x, double());
    MOCK_METHOD0(get_draw_y, double());
    MOCK_METHOD0(get_width, double());
    MOCK_METHOD0(get_height, double());

    MOCK_METHOD1(set_draw_x, void(double));
    MOCK_METHOD1(set_draw_y, void(double));
    MOCK_METHOD1(set_width, void(double));
    MOCK_METHOD1(set_height, void(double));

    MOCK_METHOD1(draw, bool(Renderer *));
    MOCK_METHOD1(update, void(double));
};

#endif /* MOCKDRAWABLE_H */
