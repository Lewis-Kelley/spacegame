#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../src/events/EventHandler.hpp"
#include "MockEvent.hpp"
#include "MockListener.hpp"

class ExposedEventHandler : public EventHandler {
 public:
    ExposedEventHandler(listener_map *map) : EventHandler(map) { }
};

class DiffMockEvent : public Event { };

TEST(AddListener, AddOneListener)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    MockListener listener;
    MockEvent event;

    handler.add_listener(&event, &listener);

    ASSERT_NE(map.find(typeid(MockEvent)), map.end());

    auto listener_list = map.at(typeid(MockEvent));
    ASSERT_EQ(1, static_cast<int>(listener_list->size()));
    ASSERT_EQ(&listener, listener_list->at(0));
}

TEST(AddListener, AddTwoListeners)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    MockListener listener1, listener2;
    MockEvent event;

    handler.add_listener(&event, &listener1);
    handler.add_listener(&event, &listener2);

    ASSERT_NE(map.find(typeid(event)), map.end());

    auto listener_list = map.at(typeid(event));
    ASSERT_EQ(2, static_cast<int>(listener_list->size()));

    bool found1 = false,
        found2 = false;

    for (Listener *listener : *listener_list) {
        if (listener == &listener1) {
            found1 = true;
        } else if (listener == &listener2) {
            found2 = true;
        }
    }

    ASSERT_TRUE(found1);
    ASSERT_TRUE(found2);
}

TEST(AddListener, AddOneListenerTwoEventTypes)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    MockListener listener;
    MockEvent event0;
    DiffMockEvent event1;

    handler.add_listener(&event0, &listener);
    handler.add_listener(&event1, &listener);

    ASSERT_NE(map.find(typeid(event0)), map.end());
    ASSERT_NE(map.find(typeid(event1)), map.end());

    ASSERT_EQ(1, static_cast<int>(map.at(typeid(event0))->size()));
    ASSERT_EQ(&listener, map.at(typeid(event0))->at(0));

    ASSERT_EQ(1, static_cast<int>(map.at(typeid(event1))->size()));
    ASSERT_EQ(&listener, map.at(typeid(event1))->at(0));
}

TEST(AddListener, AddTwoListenerTwoEventTypes)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    MockListener listener1, listener2;

    MockEvent event0;
    DiffMockEvent event1;

    handler.add_listener(&event0, &listener1);
    handler.add_listener(&event1, &listener2);

    ASSERT_NE(map.find(typeid(event0)), map.end());
    ASSERT_NE(map.find(typeid(event1)), map.end());

    ASSERT_EQ(1, static_cast<int>(map.at(typeid(event0))->size()));
    ASSERT_EQ(&listener1, map.at(typeid(event0))->at(0));

    ASSERT_EQ(1, static_cast<int>(map.at(typeid(event1))->size()));
    ASSERT_EQ(&listener2, map.at(typeid(event1))->at(0));
}

TEST(AddListener, AddNullListener)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    MockEvent event;

    ASSERT_THROW(handler.add_listener(&event, NULL),
                 EventHandler::InvalidListenerException);
}

TEST(RemoveListener, RemoveOnlyListener)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    MockListener listener;

    std::vector<Listener *> listeners;
    listeners.push_back(&listener);

    MockEvent event;

    std::pair<std::type_index, std::vector<Listener *> *>
        p(typeid(event), &listeners);
    map.insert(p);

    handler.remove_listener(&event, &listener);

    ASSERT_EQ(0, static_cast<int>(listeners.size()));
}

TEST(RemoveListener, RemoveOneOfManyListener)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    MockListener right_listener, wrong_listener;
    MockEvent event;

    std::vector<Listener *> listeners;
    listeners.push_back(&right_listener);
    listeners.push_back(&wrong_listener);

    std::pair<std::type_index, std::vector<Listener *> *>
        p(typeid(event), &listeners);
    map.insert(p);

    handler.remove_listener(&event, &right_listener);

    ASSERT_EQ(1, static_cast<int>(listeners.size()));
    ASSERT_EQ(&wrong_listener, listeners.at(0));
}

TEST(RemoveListener, RemoveFromEmptyList)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    MockListener listener;
    MockEvent event;

    ASSERT_THROW(handler.remove_listener(&event, &listener),
                 EventHandler::InvalidListenerException);
}

TEST(RemoveListener, RemoveMissingListener)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    MockListener wrong_listener, right_listener;
    MockEvent event;

    std::vector<Listener *> listeners;
    listeners.push_back(&wrong_listener);

    std::pair<std::type_index, std::vector<Listener *> *>
        p(typeid(event), &listeners);
    map.insert(p);

    ASSERT_THROW(handler.remove_listener(&event, &right_listener),
                 EventHandler::InvalidListenerException);
}

TEST(RemoveListener, RemoveMistypedListener)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    MockListener listener;
    MockEvent event;

    std::vector<Listener *> listeners;
    listeners.push_back(&listener);

    std::pair<std::type_index, std::vector<Listener *> *> pair
        (typeid(DiffMockEvent), &listeners);
    map.insert(pair);

    ASSERT_THROW(handler.remove_listener(&event, &listener),
                 EventHandler::InvalidListenerException);
}

TEST(RemoveListener, RemoveNullListener)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);
    MockEvent event;
    ASSERT_THROW(handler.remove_listener(&event, NULL),
                 EventHandler::InvalidListenerException);
}

TEST(HandleEvent, HandleNullEvent)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);
    ASSERT_THROW(handler.handle_event(NULL),
                 EventHandler::InvalidEventException);
}

TEST(HandleEvent, OneRightListener)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    std::vector<Listener *> listeners;

    MockEvent event;
    MockListener listener;

    listeners.push_back(&listener);

    map.insert(std::pair<std::type_index, std::vector<Listener *> *>
               (typeid(event), &listeners));

    EXPECT_CALL(listener, catch_event(&event)).Times(1);

    handler.handle_event(&event);
}

TEST(HandleEvent, MultipleRightListener)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    std::vector<Listener *> listeners;

    MockEvent event;
    MockListener listener1, listener2;

    listeners.push_back(&listener1);
    listeners.push_back(&listener2);

    map.insert(std::pair<const std::type_index, std::vector<Listener *> *>
               (typeid(event), &listeners));

    EXPECT_CALL(listener1, catch_event(&event)).Times(1);
    EXPECT_CALL(listener2, catch_event(&event)).Times(1);

    handler.handle_event(&event);
}

TEST(HandleEvent, OneWrongListener)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    std::vector<Listener *> listeners;

    MockEvent event;
    MockListener listener;

    listeners.push_back(&listener);

    map.insert(std::pair<std::type_index, std::vector<Listener *> *>
               (typeid(DiffMockEvent), &listeners));

    EXPECT_CALL(listener, catch_event(&event)).Times(0);

    handler.handle_event(&event);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
