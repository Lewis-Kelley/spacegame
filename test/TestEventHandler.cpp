#include <gtest/gtest.h>

#include "../src/events/EventHandler.hpp"
#include "MockEvent.hpp"
#include "MockListener.hpp"

class ExposedEventHandler : public EventHandler {
 public:
    ExposedEventHandler(listener_map *map) : EventHandler(map) { }
};

TEST(AddListener, AddOneListener)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    MockListener listener;
    Event::Event_Type type = static_cast<Event::Event_Type>(0);

    handler.add_listener(type, &listener);

    ASSERT_NE(map.find(type), map.end());

    auto listener_list = map.at(type);
    ASSERT_EQ(1, static_cast<int>(listener_list->size()));
    ASSERT_EQ(&listener, listener_list->at(0));
}

TEST(AddListener, AddTwoListeners)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    MockListener listener1, listener2;
    Event::Event_Type type = static_cast<Event::Event_Type>(0);

    handler.add_listener(type, &listener1);
    handler.add_listener(type, &listener2);

    ASSERT_NE(map.find(type), map.end());

    auto listener_list = map.at(type);
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
    auto type0 = static_cast<Event::Event_Type>(0);
    auto type1 = static_cast<Event::Event_Type>(1);

    handler.add_listener(type0, &listener);
    handler.add_listener(type1, &listener);

    ASSERT_NE(map.find(type0), map.end());
    ASSERT_NE(map.find(type1), map.end());

    ASSERT_EQ(1, static_cast<int>(map.at(type0)->size()));
    ASSERT_EQ(&listener, map.at(type0)->at(0));

    ASSERT_EQ(1, static_cast<int>(map.at(type1)->size()));
    ASSERT_EQ(&listener, map.at(type1)->at(0));
}

TEST(AddListener, AddTwoListenerTwoEventTypes)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    MockListener listener1, listener2;
    auto type0 = static_cast<Event::Event_Type>(0);
    auto type1 = static_cast<Event::Event_Type>(1);

    handler.add_listener(type0, &listener1);
    handler.add_listener(type1, &listener2);

    ASSERT_NE(map.find(type0), map.end());
    ASSERT_NE(map.find(type1), map.end());

    ASSERT_EQ(1, static_cast<int>(map.at(type0)->size()));
    ASSERT_EQ(&listener1, map.at(type0)->at(0));

    ASSERT_EQ(1, static_cast<int>(map.at(type1)->size()));
    ASSERT_EQ(&listener2, map.at(type1)->at(0));
}

TEST(AddListener, AddNullListener)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    ASSERT_THROW(handler.add_listener(static_cast<Event::Event_Type>(0), NULL),
                 EventHandler::InvalidListenerException);
}

TEST(RemoveListener, RemoveOnlyListener)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    MockListener listener;
    auto type = static_cast<Event::Event_Type>(0);

    std::vector<Listener *> listeners;
    listeners.push_back(&listener);

    std::pair<Event::Event_Type, std::vector<Listener *> *> p(type, &listeners);
    map.insert(p);

    handler.remove_listener(type, &listener);

    ASSERT_EQ(0, static_cast<int>(listeners.size()));
}

TEST(RemoveListener, RemoveOneOfManyListener)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    MockListener right_listener, wrong_listener;
    auto type = static_cast<Event::Event_Type>(0);

    std::vector<Listener *> listeners;
    listeners.push_back(&right_listener);
    listeners.push_back(&wrong_listener);

    std::pair<Event::Event_Type, std::vector<Listener *> *> p(type, &listeners);
    map.insert(p);

    handler.remove_listener(type, &right_listener);

    ASSERT_EQ(1, static_cast<int>(listeners.size()));
    ASSERT_EQ(&wrong_listener, listeners.at(0));
}

TEST(RemoveListener, RemoveFromEmptyList)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    MockListener listener;
    ASSERT_THROW(handler.remove_listener(static_cast<Event::Event_Type>(0),
                                         &listener),
                 EventHandler::InvalidListenerException);
}

TEST(RemoveListener, RemoveMissingListener)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    MockListener wrong_listener, right_listener;
    Event::Event_Type type = static_cast<Event::Event_Type>(0);

    std::vector<Listener *> listeners;
    listeners.push_back(&wrong_listener);

    std::pair<Event::Event_Type, std::vector<Listener *> *> p(type, &listeners);
    map.insert(p);

    ASSERT_THROW(handler.remove_listener(type, &right_listener),
                 EventHandler::InvalidListenerException);
}

TEST(RemoveListener, RemoveMistypedListener)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    MockListener listener;

    std::vector<Listener *> listeners;
    listeners.push_back(&listener);

    std::pair<Event::Event_Type, std::vector<Listener *> *> pair
        (static_cast<Event::Event_Type>(0), &listeners);
    map.insert(pair);

    ASSERT_THROW(handler.remove_listener(static_cast<Event::Event_Type>(1),
                                         &listener),
                 EventHandler::InvalidListenerException);
}

TEST(RemoveListener, RemoveNullListener)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);
    ASSERT_THROW(handler.remove_listener(static_cast<Event::Event_Type>(0),
                                         NULL),
                 EventHandler::InvalidListenerException);
}

TEST(HandleEvent, HandleNullEvent)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);
    ASSERT_THROW(handler.handle_event(NULL),
                 EventHandler::InvalidEventException);
}

TEST(HandleEvent, NoListeners)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    MockEvent event;

    EXPECT_CALL(event, get_type());

    handler.handle_event(&event);
}

TEST(HandleEvent, OneRightListener)
{
    EventHandler::listener_map map;
    ExposedEventHandler handler(&map);

    std::vector<Listener *> listeners;

    MockEvent event;
    MockListener listener;
    Event::Event_Type type = static_cast<Event::Event_Type>(0);

    listeners.push_back(&listener);

    map.insert(std::pair<Event::Event_Type, std::vector<Listener *> *>
               (type, &listeners));

    EXPECT_CALL(event, get_type()).WillRepeatedly(testing::Return(type));
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
    Event::Event_Type type = static_cast<Event::Event_Type>(0);

    listeners.push_back(&listener1);
    listeners.push_back(&listener2);

    map.insert(std::pair<Event::Event_Type, std::vector<Listener *> *>
               (type, &listeners));

    EXPECT_CALL(event, get_type()).WillRepeatedly(testing::Return(type));
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

    map.insert(std::pair<Event::Event_Type, std::vector<Listener *> *>
               (static_cast<Event::Event_Type>(0), &listeners));

    EXPECT_CALL(event, get_type())
        .WillRepeatedly(testing::Return(static_cast<Event::Event_Type>(1)));
    EXPECT_CALL(listener, catch_event(&event)).Times(0);

    handler.handle_event(&event);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
