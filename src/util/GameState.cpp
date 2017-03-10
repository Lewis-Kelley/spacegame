#include "GameState.hpp"

std::vector<Drawable *> gamestate::drawings;
int gamestate::tile_size = 50;
bool gamestate::running = false;

void gamestate::draw_all(double delta)
{
    for (int i = 0; i < (int)drawings.size(); i++) {
        drawings.at(i)->update(delta);
        drawings.at(i)->draw();
    }
}
