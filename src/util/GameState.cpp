#include "GameState.hpp"

GameState *GameState::self = nullptr;

GameState::GameState(Window *wind)
    : wind(wind), running(false), tile_size(50) { }

GameState *GameState::get_instance()
{
    if (self == nullptr) {
        self = new GameState(Window::get_instance());
    }

    return self;
}

void GameState::draw_all(double delta)
{
    Renderer *rend = wind->get_rend();

    for (int i = 0; i < static_cast<int>(drawings.size()); i++) {
        drawings.at(i)->update(delta);
        drawings.at(i)->draw(rend);
    }
}
