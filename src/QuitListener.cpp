#include "QuitListener.hpp"

void QuitListener::catch_event(Event *event) {
    if (event->get_type() == Event::QUIT) {
        gamestate::running = false;
    }
}
