#include "GameState.hpp"

GameState *GameState::self = nullptr;

GameState::GameState()
{
    running = false;
    tile_size = 50;
}

GameState *GameState::get_instance()
{
    if (self == nullptr) {
        self = new GameState();
    }

    return self;
}

void GameState::draw_all(double delta)
{
    Window *wind = Window::get_instance();
    Renderer *rend = wind->get_rend();

    for (int i = 0; i < static_cast<int>(drawings.size()); i++) {
        drawings.at(i)->update(delta);
        drawings.at(i)->draw(rend);
    }
}
