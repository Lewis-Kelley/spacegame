#include "GameState.hpp"

bool gamestate::running;
std::vector<Drawable *> gamestate::drawings;

void gamestate::draw_all(double delta)
{
    for (int i = 0; i < (int)drawings.size(); i++) {
        drawings.at(i)->update(delta);
        drawings.at(i)->draw();
    }
}
