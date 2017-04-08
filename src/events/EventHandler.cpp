#include "EventHandler.hpp"

EventHandler *EventHandler::self;
EventHandler::listener_key_t EventHandler::next_listener_key = 0;

EventHandler *EventHandler::get_instance()
{
    if (self == NULL) {
        self = new EventHandler();
    }

    return self;
}

void EventHandler::reset()
{
    if (self != NULL) {
        delete self;
    }

    self = new EventHandler();
}

EventHandler::~EventHandler()
{
    if (listeners != NULL && !given_map) {
        delete listeners;
    }
}

/**
 * Calls any listeners that are waiting for the passed event.
 *
 * @param event The SDL_Event to handle.
 */
void EventHandler::handle_event(Event *event) const
{
    if (event == nullptr) {
        throw InvalidEventException("Passed Event was NULL.\n");
    }

    if (listeners->find(typeid(*event)) != listeners->end()) {
        auto callees = listeners->at(typeid(*event));
        for (int i = 0; i < static_cast<int>(callees->size()); i++) {
            callees->at(i).second(event);
        }
    }
}

/**
 * Adds a new Listener to the handler with the given information.
 *
 * @param type The type of the event this Listener should listen for.
 * @param obs The Listener to add to the observer list.
 */
EventHandler::listener_key_t
EventHandler::add_listener(Event *sample_event, listener_t obs)
{
    typedef std::pair<std::type_index, std::vector<listener_pair_t> *>
        type_listeners_pair;

    if (sample_event == NULL) {
        throw InvalidEventException("Cannot listen for NULL Events.\n");
    }

    std::type_index type(typeid(*sample_event));

    if (listeners->find(type) == listeners->end()) {
        auto *vec = new std::vector<listener_pair_t>();
        listeners->insert(type_listeners_pair(type, vec));
    }

    listeners->at(type)->push_back(listener_pair_t(next_listener_key, obs));
    return next_listener_key++;
}

/**
 * Remove the given Listener from the call list with the given
 * event_code.
 *
 * @param type The type of Event from which to remove obs.
 * @param obs The Listener to remove.
 */
void EventHandler::remove_listener(listener_key_t key)
{
    auto map_pair = listeners->begin();
    while (map_pair != listeners->end()) {
        for (int i = 0; i < static_cast<int>(map_pair->second->size()); i++) {
            if (map_pair->second->at(i).first == key) {
                map_pair->second->erase(map_pair->second->begin() + i);
                return;
            }
        }

        map_pair++;
    }

    throw InvalidListenerException("Listener not found in.\n");
}
