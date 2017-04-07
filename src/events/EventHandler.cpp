#include "EventHandler.hpp"

EventHandler *EventHandler::self;

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
    if (event == NULL) {
        throw InvalidEventException("Passed Event was NULL.\n");
    }

    if (listeners->find(typeid(*event)) != listeners->end()) {
        for (Listener *listener : *listeners->at(typeid(*event))) {
            listener->catch_event(event);
        }
    }
}

/**
 * Adds a new Listener to the handler with the given information.
 *
 * @param type The type of the event this Listener should listen for.
 * @param obs The Listener to add to the observer list.
 */
void EventHandler::add_listener(Event *sample_event, Listener *obs)
{
    if (obs == NULL) {
        throw InvalidListenerException("Attempting to add NULL Listener.\n");
    }

    if (sample_event == NULL) {
        throw InvalidEventException("Cannot listen for NULL Events.\n");
    }

    std::type_index type(typeid(*sample_event));

    typedef std::pair<std::type_index, std::vector<Listener *> *>
        type_listeners_pair;

    if (listeners->find(type) == listeners->end()) {
        std::vector<Listener *> *vec = new std::vector<Listener *>();
        listeners->insert(type_listeners_pair(type, vec));
    }

    listeners->at(type)->push_back(obs);
}

/**
 * Remove the given Listener from the call list with the given
 * event_code.
 *
 * @param type The type of Event from which to remove obs.
 * @param obs The Listener to remove.
 */
void EventHandler::remove_listener(Event *sample_event, Listener *obs)
{
    if (obs == NULL) {
        throw InvalidListenerException("Attempting to remove NULL Listener.\n");
    }

    std::vector<Listener *> *vec;
    std::type_index type(typeid(*sample_event));

    if (listeners->find(type) == listeners->end()) { // Key doesn't exist
        throw InvalidListenerException("Listener not found in given type.\n");
    }

    vec = listeners->at(type);

    for (int i = 0; i < (int)vec->size(); i++) {
        if (vec->at(i) == obs) {
            vec->erase(vec->begin() + i);
            return;
        }
    }

    throw InvalidListenerException("Listener not found in given type.\n");
}
