#include "Sprite.hpp"

/**
 * @param src_rect The SDL_Rect defining what subsection of tex to use
 * as this Sprite.
 * @param dest_rect The SDL_Rect defining where to draw the Sprite
 * onscreen.
 * @param tex A pointer to an SDL_Texture holding the image data to draw.
 */
Sprite::Sprite(SDL_Rect src_rect, SDL_Rect dest_rect, SDL_Texture *tex) {
    wind = Window::get_instance();
    this->tex = tex;
    this->src_rect = new SDL_Rect();
    *this->src_rect = src_rect;
    this->dest_rect = new SDL_Rect();
    *this->dest_rect = dest_rect;
    given_tex = true;
    dx = 0;
    dy = 0;
}

/**
 * This constructor should be used when either the Sprite should take
 * up the whole screen or the whole texture.
 *
 * @param rect The SDL_Rect either defining what subsection of tex to
 * use as this Sprite or where to draw the Sprite onscreen, depending
 * on dest.
 * @param tex A pointer to an SDL_Texture holding the image data to draw.
 * @param dest True if the passed rect shows where to draw the Sprite, false
 * if it shows where the Sprite comes from.
 */
Sprite::Sprite(SDL_Rect rect, SDL_Texture *tex, bool dest) {
    wind = Window::get_instance();
    SDL_Rect **target_rect;
    SDL_Rect **other_rect;

    this->tex = tex;

    if (dest) {
        target_rect = &dest_rect;
        other_rect = &src_rect;
    } else {
        target_rect = &src_rect;
        other_rect = &dest_rect;
    }

    *target_rect = new SDL_Rect();
    **target_rect = rect;
    *other_rect = NULL;
    given_tex = true;
    dx = 0;
    dy = 0;
}

/**
 * This constructor should be used when the whole image file should be used,
 * and the Sprite should take up the whole screen.
 *
 * @param tex A pointer to an SDL_Texture holding the image data to draw.
 */
Sprite::Sprite(SDL_Texture *tex) {
    wind = Window::get_instance();
    this->tex = tex;
    src_rect = NULL;
    dest_rect = NULL;
    given_tex = true;
    dx = 0;
    dy = 0;
}

/**
 * @param src_rect The SDL_Rect defining what subsection of tex to use
 * as this Sprite.
 * @param dest_rect The SDL_Rect defining where to draw the Sprite
 * onscreen.
 * @param filename The name of the image file to load this Sprite from.
 */
Sprite::Sprite(SDL_Rect src_rect, SDL_Rect dest_rect, std::string filename) {
    wind = Window::get_instance();
    this->tex = load_texture(filename);
    this->src_rect = new SDL_Rect();
    *this->src_rect = src_rect;
    this->dest_rect = new SDL_Rect();
    *this->dest_rect = dest_rect;
    given_tex = false;
    dx = 0;
    dy = 0;
}

/**
 * This constructor should be used when either the Sprite should take
 * up the whole screen or the whole texture.
 *
 * @param rect The SDL_Rect either defining what subsection of tex to
 * use as this Sprite or where to draw the Sprite onscreen, depending
 * on dest.
 * @param filename The name of the image file to load this Sprite from.
 * @param dest True if the passed rect shows where to draw the Sprite, false
 * if it shows where the Sprite comes from.
 */
Sprite::Sprite(SDL_Rect rect, std::string filename, bool dest) {
    wind = Window::get_instance();
    SDL_Rect **target_rect;
    SDL_Rect **other_rect;

    this->tex = load_texture(filename);

    if (dest) {
        target_rect = &dest_rect;
        other_rect = &src_rect;
    } else {
        target_rect = &src_rect;
        other_rect = &dest_rect;
    }

    *target_rect = new SDL_Rect();
    **target_rect = rect;
    *other_rect = NULL;
    given_tex = false;
    dx = 0;
    dy = 0;
}

/**
 * This constructor should be used when the whole image file should be used,
 * and the Sprite should take up the whole screen.
 *
 * @param filename The name of the image file to load this Sprite from.
 */
Sprite::Sprite(std::string filename) {
    wind = Window::get_instance();
    this->tex = load_texture(filename);
    src_rect = NULL;
    dest_rect = NULL;
    given_tex = false;
    dx = 0;
    dy = 0;
}

/**
 * Frees the stored SDL_Rect's, but not the SDL_Texture if it was passed into
 * the constructor.
 */
Sprite::~Sprite() {
    if (src_rect != NULL) {
        delete src_rect;
        src_rect = NULL;
    }

    if (dest_rect != NULL) {
        delete dest_rect;
        dest_rect = NULL;
    }

    if (!given_tex && tex != NULL) {
        SDL_DestroyTexture(tex);
        tex = NULL;
    }
}

/**
 * Load the texture in the file located at the filename.
 *
 * @param filename The path to the image file.
 * @return A new SDL_Texture based of the image file.
 */
SDL_Texture *Sprite::load_texture(std::string filename) {
    SDL_Texture *tex = NULL;
    SDL_Surface *img = IMG_Load(filename.c_str());
    Window *wind = Window::get_instance();

    if (img == NULL) {
        throw IMG_GetError();
    }

    // Set invisible color
    SDL_SetColorKey(img, SDL_TRUE, SDL_MapRGB(img->format, 0xFF, 0x00, 0xFF));
    // Create texture from the surface
    tex = SDL_CreateTextureFromSurface(wind->get_renderer(), img);

    if (tex == NULL) {
        throw IMG_GetError();
    }

    return tex;
}

/**
 * Draws the Sprite onscreen.
 *
 * @return True if successfully renderer, false otherwise.
 */
bool Sprite::draw() {
    return SDL_RenderCopy(wind->get_renderer(), tex, src_rect, dest_rect);
}

/**
 * Move the sprite according to its dx, dy, and the time passed.
 *
 * @param delta The amount of time passed since the last tick.
 */
void Sprite::update(double delta) {
    dest_rect->x += delta * dx;
    dest_rect->y += delta * dy;
}
