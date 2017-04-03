#ifndef MOCKEVENT_H
#define MOCKEVENT_H

#include <gmock/gmock.h>

#include "../src/events/Event.hpp"

class MockEvent : public Event {
 public:
    MOCK_METHOD0(get_type, Event_Type());
};

#endif /* MOCKEVENT_H */
