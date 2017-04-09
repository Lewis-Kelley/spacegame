#ifndef MOCKGAMESTATE_H
#define MOCKGAMESTATE_H

#include <gmock/gmock.h>

#include "../../src/util/GameState.hpp"

class MockGameState : public GameState {
public:
    MockGameState(Window *wind) : GameState(wind) { }

    MOCK_METHOD1(draw_all, void(double));
    MOCK_METHOD0(get_is_running, bool());
    MOCK_METHOD1(set_is_running, void(bool));
};

#endif /* MOCKGAMESTATE_H */
