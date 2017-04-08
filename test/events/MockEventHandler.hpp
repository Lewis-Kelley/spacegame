#ifndef MOCKEVENTHANDLER_H
#define MOCKEVENTHANDLER_H

#include <gmock/gmock.h>

#include "../../src/events/EventHandler.hpp"

class MockEventHandler : public EventHandler {
 public:
    MockEventHandler() : EventHandler(new listener_map_t()) { }

    // Constructor resets the super so that the map is deleted.
    ~MockEventHandler() { EventHandler::reset(); }

    MOCK_METHOD1(handle_event, void(Event *));
    MOCK_METHOD2(add_listener, listener_key_t(Event *, listener_t));
    MOCK_METHOD1(remove_listener, void(listener_key_t));
};

#endif /* MOCKEVENTHANDLER_H */
