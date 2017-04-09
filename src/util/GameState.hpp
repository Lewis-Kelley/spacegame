#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <vector>

#include "Window.hpp"
#include "../drawables/Drawable.hpp"

class GameState {
 private:
    static GameState *self;

    Window *wind;
    bool running;

 protected:
    GameState(Window *wind);

 public:
    static GameState *get_instance();

    std::vector<Drawable *> drawings;
    int tile_size;

    virtual bool get_is_running() { return running; }
    virtual void set_is_running(bool running) { this->running = running; }

    virtual void draw_all(double delta);
};

#endif /* GAMESTATE_H */
