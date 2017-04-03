#include <gmock/gmock.h>

#include "../src/listeners/Listener.hpp"

class MockListener : public Listener {
 public:
    MOCK_METHOD1(catch_event, void(Event *));
};
