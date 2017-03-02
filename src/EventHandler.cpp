#include "EventHandler.hpp"

std::map<Event::Event_Type, std::vector<Listener *>*> event_handler::listeners;

/**
 * Calls any listeners that are waiting for the passed event.
 *
 * @param event The SDL_Event to handle.
 */
void event_handler::handle_event(Event *event)
{
    try {
        std::vector<Listener *>* values = listeners.at(event->get_type());
        for (int i = 0; i < (int)values->size(); i++) {
            values->at(i)->catch_event(event);
        }
    } catch (std::out_of_range err) {
        fprintf(stderr, "No available listeners for event type %d.\n",
                event->get_type());
    }
}

/**
 * Adds a new Listener to the handler with the given information.
 *
 * @param type The type of the event this Listener should listen for.
 * @param obs The Listener to add to the observer list.
 */
void event_handler::add_listener(Event::Event_Type type, Listener *obs)
{
    if (listeners.find(type) == listeners.end()) { // Key doesn't exist
        std::vector<Listener *> *vec = new std::vector<Listener *>();
        listeners.insert(std::pair<Event::Event_Type,
                         std::vector<Listener *>*>(type, vec));
    }

    listeners.at(type)->push_back(obs);
}

/**
 * Remove the given Listener from the call list with the given
 * event_code.
 *
 * @param type The type of Event from which to remove obs.
 * @param obs The Listener to remove.
 */
void event_handler::remove_listener(Event::Event_Type type, Listener *obs)
{
    std::vector<Listener *> *vec;

    if (listeners.find(type) == listeners.end()) { // Key doesn't exist
        return;
    }

    vec = listeners.at(type);

    for (int i = 0; i < (int)vec->size(); i++) {
        if (vec->at(i) == obs) {
            vec->erase(vec->begin() + i);
            i--;
        }
    }
}
