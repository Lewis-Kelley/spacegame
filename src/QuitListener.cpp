#include "QuitListener.hpp"

QuitListener::QuitListener()
{
    event_handler::add_listener(Event::QUIT, this);
}

void QuitListener::catch_event(Event *event)
{
    if (event->get_type() == Event::QUIT) {
        gamestate::running = false;
    }
}
