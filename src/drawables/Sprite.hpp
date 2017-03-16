#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <string>

#include "../util/Window.hpp"
#include "Drawable.hpp"

/**
 * Convinence class that basically just wraps an SDL_Texture.
 */
class Sprite : public Drawable {
private:
    double x; ///< The full-detail x position.
    double y; ///< The full-detail y position.
    SDL_Texture *tex; ///< The SDL_Texture that actually holds the Sprite.
    SDL_Rect *src_rect; ///< The source rectangle of the Sprite.
    SDL_Rect *dest_rect; ///< The rectangle of where the Sprite will be drawn.
    bool given_tex; ///< Used to decide whether or not to destroy tex.
protected:
    double get_draw_x();
    double get_draw_y();
    double get_width();
    double get_height();
    void set_draw_x(double x);
    void set_draw_y(double y);
    void set_width(double width);
    void set_height(double height);
public:
    Sprite(SDL_Rect src_rect, SDL_Rect dest_rect, SDL_Texture *tex);
    Sprite(SDL_Rect rect, SDL_Texture *tex, bool dest);
    Sprite(SDL_Texture *tex);
    ~Sprite();
    virtual bool draw(Renderer *rend);
};

#endif /* SPRITE_H */
