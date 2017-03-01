#ifndef QUIT_LISTENER_H
#define QUIT_LISTENER_H

#include "Listener.hpp"
#include "GameState.hpp"

/**
 * Catches a QUIT Event and quits the game.
 */
class QuitListener : public Listener {
public:
    void catch_event(Event *event);
};

#endif /* QUIT_LISTENER_H */
