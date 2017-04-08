#include "QuitListener.hpp"

void QuitListener::add_as_listener(EventHandler *handler)
{
    QuitEvent quit_event;
    handler->add_listener(&quit_event, [this](Event *event)
                          { handle_quit(event); });
}

void QuitListener::handle_quit(Event *)
{
    state->set_is_running(false);
}
