#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include <string>

#include "window.hpp"
#include "drawable.hpp"

/**
 * Convinence class that basically just wraps an SDL_Texture.
 */
class sprite : drawable {
private:
    window *wind; ///< The information about the SDL renderer.
    SDL_Texture *tex; ///< The SDL_Texture that actually holds the sprite.
    SDL_Rect *src_rect; ///< The source rectangle of the sprite.
    SDL_Rect *dest_rect; ///< The rectangle of where the sprite will be drawn.
    bool given_tex; ///< Used to decide whether or not to destroy tex.
public:
    sprite(SDL_Rect src_rect, SDL_Rect dest_rect, SDL_Texture *tex);
    sprite(SDL_Rect rect, SDL_Texture *tex, bool dest);
    sprite(SDL_Texture *tex);
    sprite(SDL_Rect src_rect, SDL_Rect dest_rect, std::string filename);
    sprite(SDL_Rect rect, std::string filename, bool dest);
    sprite(std::string filename);
    ~sprite();
    static SDL_Texture *load_texture(std::string filename);
    bool draw();
};

#endif /* SPRITE_H */
