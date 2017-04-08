#include "QuitListener.hpp"

QuitListener::QuitListener()
{
    auto handler = EventHandler::get_instance();

    QuitEvent quit_event;
    handler->add_listener(&quit_event, [this](Event *event)
                          { handle_quit(event); });
}

void QuitListener::handle_quit(Event *)
{
    gamestate::running = false;
}
