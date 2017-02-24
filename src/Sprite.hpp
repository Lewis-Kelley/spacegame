#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <string>

#include "Window.hpp"
#include "Drawable.hpp"

/**
 * Convinence class that basically just wraps an SDL_Texture.
 */
class Sprite : public Drawable {
private:
    Window *wind; ///< The information about the SDL renderer.
    SDL_Texture *tex; ///< The SDL_Texture that actually holds the Sprite.
    SDL_Rect *src_rect; ///< The source rectangle of the Sprite.
    SDL_Rect *dest_rect; ///< The rectangle of where the Sprite will be drawn.
    bool given_tex; ///< Used to decide whether or not to destroy tex.
public:
    Sprite(SDL_Rect src_rect, SDL_Rect dest_rect, SDL_Texture *tex);
    Sprite(SDL_Rect rect, SDL_Texture *tex, bool dest);
    Sprite(SDL_Texture *tex);
    Sprite(SDL_Rect src_rect, SDL_Rect dest_rect, std::string filename);
    Sprite(SDL_Rect rect, std::string filename, bool dest);
    Sprite(std::string filename);
    ~Sprite();
    static SDL_Texture *load_texture(std::string filename);
    bool draw();
};

#endif /* SPRITE_H */
