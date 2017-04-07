#include "QuitListener.hpp"

QuitListener::QuitListener()
{
    auto handler = EventHandler::get_instance();

    QuitEvent quit_event;
    handler->add_listener(&quit_event, this);
}

void QuitListener::catch_event(Event *)
{
    gamestate::running = false;
}
