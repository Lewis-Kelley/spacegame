#ifndef QUIT_LISTENER_H
#define QUIT_LISTENER_H

#include "Listener.hpp"
#include "../util/GameState.hpp"
#include "../events/EventHandler.hpp"
#include "../events/QuitEvent.hpp"

/**
 * Catches a QUIT Event and quits the game.
 */
class QuitListener : public Listener {
 public:
    QuitListener();
    void catch_event(Event *event);
};

#endif /* QUIT_LISTENER_H */
