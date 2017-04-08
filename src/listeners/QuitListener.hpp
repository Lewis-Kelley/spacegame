#ifndef QUIT_LISTENER_H
#define QUIT_LISTENER_H

#include "../util/GameState.hpp"
#include "../events/EventHandler.hpp"
#include "../events/QuitEvent.hpp"

/**
 * Catches a QUIT Event and quits the game.
 */
class QuitListener {
 private:
    GameState *state;

 public:
    QuitListener(GameState *state) : state(state) { }
    virtual void add_as_listener(EventHandler *handler);
    virtual void handle_quit(Event *event);
};

#endif /* QUIT_LISTENER_H */
