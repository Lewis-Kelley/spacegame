#include "QuitListener.hpp"

void QuitListener::catch_event(Event *event) {
    gamestate::running = false;
}
