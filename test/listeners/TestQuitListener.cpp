#include <gtest/gtest.h>

#include "../util/MockWindow.hpp"
#include "../util/MockGameState.hpp"
#include "../../src/listeners/QuitListener.hpp"
#include "../events/MockEventHandler.hpp"

class PMockQuitListener : public QuitListener {
public:
    PMockQuitListener(GameState *state) : QuitListener(state) { }
    MOCK_METHOD1(handle_quit, void(Event *));
};

bool run_callback(std::function<void(Event *)> callback)
{
    callback(nullptr);
    return true;
}

TEST(AddAsListener, AddToHandlerMap)
{
    MockEventHandler handler;
    MockWindow wind;
    MockGameState state(&wind);

    PMockQuitListener quit_listener(&state);

    EXPECT_CALL(quit_listener, handle_quit(nullptr)).Times(1);
    EXPECT_CALL(handler, add_listener(testing::_, testing::_)).Times(1)
        .WillOnce(testing::WithArg<1>(testing::Invoke(run_callback)));
    quit_listener.add_as_listener(&handler);
}

TEST(HandleQuit, RunningFalse)
{
    MockWindow wind;
    MockGameState state(&wind);
    QuitListener quit_listener(&state);

    EXPECT_CALL(state, set_is_running(false));
    quit_listener.handle_quit(nullptr);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
