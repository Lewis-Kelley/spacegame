#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/util/GameState.hpp"
#include "MockWindow.hpp"
#include "../drawables/MockDrawable.hpp"
#include "../drawables/MockRenderer.hpp"

class PMockGameState : public GameState {
 public:
    PMockGameState(Window *wind) : GameState(wind) { }
};

TEST(DrawAll, EmptyList)
{
    MockWindow wind;
    PMockGameState state(&wind);

    state.draw_all(1.2);
}

TEST(DrawAll, SingleElement)
{
    double delta = 1.2;
    MockWindow wind;
    MockRenderer rend;
    PMockGameState state(&wind);
    MockDrawable drawable;

    state.drawings.push_back(&drawable);

    EXPECT_CALL(drawable, update(delta)).Times(1);
    EXPECT_CALL(drawable, draw(&rend)).Times(1);
    EXPECT_CALL(wind, get_rend()).Times(1).WillOnce(testing::Return(&rend));

    state.draw_all(delta);
}

TEST(DrawAll, TwoElements)
{
    double delta = 1.2;
    MockWindow wind;
    MockRenderer rend;
    PMockGameState state(&wind);
    MockDrawable drawable1, drawable2;

    state.drawings.push_back(&drawable1);
    state.drawings.push_back(&drawable2);

    EXPECT_CALL(drawable1, update(delta)).Times(1);
    EXPECT_CALL(drawable1, draw(&rend)).Times(1);

    EXPECT_CALL(drawable2, update(delta)).Times(1);
    EXPECT_CALL(drawable2, draw(&rend)).Times(1);

    EXPECT_CALL(wind, get_rend()).Times(1).WillOnce(testing::Return(&rend));

    state.draw_all(delta);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
