#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "../../src/events/EventHandler.hpp"
#include "MockEvent.hpp"

class ExposedEventHandler : public EventHandler {
 public:
    ExposedEventHandler(listener_map_t *map) : EventHandler(map) { }
};

class DiffMockEvent : public Event { };

void listener_func_a(Event *) { }
void listener_func_b(Event *) { }

TEST(AddListener, AddOneListenerLambda)
{
    EventHandler::listener_map_t map;
    ExposedEventHandler handler(&map);

    MockEvent event;

    EventHandler::listener_key_t listener_handle
        = handler.add_listener(&event, [](Event *){});

    ASSERT_NE(map.find(typeid(MockEvent)), map.end());

    auto listener_list = map.at(typeid(MockEvent));
    ASSERT_EQ(1, static_cast<int>(listener_list->size()));
    ASSERT_EQ(listener_handle, listener_list->at(0).first);
}

TEST(AddListener, AddOneListenerFunc)
{
    EventHandler::listener_map_t map;
    ExposedEventHandler handler(&map);

    MockEvent event;

    EventHandler::listener_key_t listener_handle
        = handler.add_listener(&event, listener_func_a);

    ASSERT_NE(map.find(typeid(MockEvent)), map.end());

    auto listener_list = map.at(typeid(MockEvent));
    ASSERT_EQ(1, static_cast<int>(listener_list->size()));
    ASSERT_EQ(listener_handle, listener_list->at(0).first);
}

TEST(AddListener, AddTwoListeners)
{
    EventHandler::listener_map_t map;
    ExposedEventHandler handler(&map);

    MockEvent event;

    EventHandler::listener_key_t listener_a_handle
        = handler.add_listener(&event, listener_func_a);
    EventHandler::listener_key_t listener_b_handle
        = handler.add_listener(&event, listener_func_b);

    ASSERT_NE(map.find(typeid(event)), map.end());

    auto listener_list = map.at(typeid(event));
    ASSERT_EQ(2, static_cast<int>(listener_list->size()));

    bool found1 = false,
        found2 = false;

    for (auto listener_pair : *listener_list) {
        if (listener_pair.first == listener_a_handle) {
            found1 = true;
        } else if (listener_pair.first == listener_b_handle) {
            found2 = true;
        }
    }

    ASSERT_TRUE(found1);
    ASSERT_TRUE(found2);
}

TEST(AddListener, AddOneListenerTwoEventTypes)
{
    EventHandler::listener_map_t map;
    ExposedEventHandler handler(&map);

    MockEvent event0;
    DiffMockEvent event1;

    EventHandler::listener_key_t handle_1
        = handler.add_listener(&event0, listener_func_a);
    EventHandler::listener_key_t handle_2
        = handler.add_listener(&event1, listener_func_b);

    ASSERT_NE(map.find(typeid(event0)), map.end());
    ASSERT_NE(map.find(typeid(event1)), map.end());

    ASSERT_EQ(1, static_cast<int>(map.at(typeid(event0))->size()));
    ASSERT_EQ(handle_1, map.at(typeid(event0))->at(0).first);

    ASSERT_EQ(1, static_cast<int>(map.at(typeid(event1))->size()));
    ASSERT_EQ(handle_2, map.at(typeid(event1))->at(0).first);
}

TEST(AddListener, AddTwoListenerTwoEventTypes)
{
    EventHandler::listener_map_t map;
    ExposedEventHandler handler(&map);

    MockEvent event0;
    DiffMockEvent event1;

    EventHandler::listener_key_t handle_a
        = handler.add_listener(&event0, listener_func_a);
    EventHandler::listener_key_t handle_b
        = handler.add_listener(&event1, listener_func_b);

    ASSERT_NE(map.find(typeid(event0)), map.end());
    ASSERT_NE(map.find(typeid(event1)), map.end());

    ASSERT_EQ(1, static_cast<int>(map.at(typeid(event0))->size()));
    ASSERT_EQ(handle_a, map.at(typeid(event0))->at(0).first);

    ASSERT_EQ(1, static_cast<int>(map.at(typeid(event1))->size()));
    ASSERT_EQ(handle_b, map.at(typeid(event1))->at(0).first);
}

TEST(RemoveListener, RemoveOnlyListener)
{
    EventHandler::listener_key_t key = 0;
    EventHandler::listener_map_t map;
    ExposedEventHandler handler(&map);

    std::vector<EventHandler::listener_pair_t> listeners;
    listeners.push_back(EventHandler::listener_pair_t(key, [](Event *){}));

    MockEvent event;

    std::pair<std::type_index, std::vector<EventHandler::listener_pair_t> *>
        p(typeid(event), &listeners);
    map.insert(p);

    handler.remove_listener(key);

    ASSERT_EQ(0, static_cast<int>(listeners.size()));
}

TEST(RemoveListener, RemoveOneOfManyListener)
{
    EventHandler::listener_map_t map;
    ExposedEventHandler handler(&map);

    MockEvent event;
    EventHandler::listener_key_t right_key = 0,
        wrong_key = 1;

    std::vector<EventHandler::listener_pair_t> listeners;
    listeners.push_back(EventHandler::listener_pair_t(right_key,
                                                      [](Event *){}));
    listeners.push_back(EventHandler::listener_pair_t(wrong_key,
                                                      [](Event *){}));

    std::pair<std::type_index, std::vector<EventHandler::listener_pair_t> *>
        p(typeid(event), &listeners);
    map.insert(p);

    handler.remove_listener(right_key);

    ASSERT_EQ(1, static_cast<int>(listeners.size()));
    ASSERT_EQ(wrong_key, listeners.at(0).first);
}

TEST(RemoveListener, RemoveFromEmptyList)
{
    EventHandler::listener_map_t map;
    ExposedEventHandler handler(&map);

    MockEvent event;
    EventHandler::listener_key_t missing_key = 0;

    ASSERT_THROW(handler.remove_listener(missing_key),
                 EventHandler::InvalidListenerException);
}

TEST(RemoveListener, RemoveMissingListener)
{
    EventHandler::listener_map_t map;
    ExposedEventHandler handler(&map);

    MockEvent event;
    EventHandler::listener_key_t wrong_key = 0,
        right_key = 1;

    std::vector<EventHandler::listener_pair_t> listeners;
    listeners.push_back(EventHandler::listener_pair_t(wrong_key,
                                                      [](Event *){}));

    std::pair<std::type_index, std::vector<EventHandler::listener_pair_t> *>
        p(typeid(event), &listeners);
    map.insert(p);

    ASSERT_THROW(handler.remove_listener(right_key),
                 EventHandler::InvalidListenerException);
}

TEST(HandleEvent, HandleNullEvent)
{
    EventHandler::listener_map_t map;
    ExposedEventHandler handler(&map);
    ASSERT_THROW(handler.handle_event(nullptr),
                 EventHandler::InvalidEventException);
}

TEST(HandleEvent, OneRightListener)
{
    EventHandler::listener_map_t map;
    ExposedEventHandler handler(&map);

    std::vector<EventHandler::listener_pair_t> listeners;

    MockEvent event;
    int called = 0;

    listeners.push_back(EventHandler::listener_pair_t(0, [&called](Event *)
                                                      { called++; }));

    map.insert(std::pair<std::type_index,
               std::vector<EventHandler::listener_pair_t> *>
               (typeid(event), &listeners));

    handler.handle_event(&event);

    ASSERT_EQ(1, called);
}

TEST(HandleEvent, MultipleRightListener)
{
    EventHandler::listener_map_t map;
    ExposedEventHandler handler(&map);

    std::vector<EventHandler::listener_pair_t> listeners;

    MockEvent event;

    int called1 = 0;
    int called2 = 0;

    listeners.push_back(EventHandler::listener_pair_t(1, [&called1](Event *)
                                                      { called1++; }));
    listeners.push_back(EventHandler::listener_pair_t(2, [&called2](Event *)
                                                      { called2++; }));

    map.insert(std::pair<const std::type_index,
               std::vector<EventHandler::listener_pair_t> *>
               (typeid(event), &listeners));

    handler.handle_event(&event);

    ASSERT_EQ(1, called1);
    ASSERT_EQ(1, called2);
}

TEST(HandleEvent, OneWrongListener)
{
    EventHandler::listener_map_t map;
    ExposedEventHandler handler(&map);

    std::vector<EventHandler::listener_pair_t> listeners;

    MockEvent event;

    int called = 0;
    listeners.push_back(EventHandler::listener_pair_t(0, [&called](Event *)
                                                      { called++; }));

    map.insert(std::pair<std::type_index,
               std::vector<EventHandler::listener_pair_t> *>
               (typeid(DiffMockEvent), &listeners));

    handler.handle_event(&event);

    ASSERT_EQ(0, called);
}

int main(int argc, char *argv[])
{
    testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}
