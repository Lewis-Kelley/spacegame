#include "Sprite.hpp"

/**
 * @param src_rect The SDL_Rect defining what subsection of tex to use
 * as this Sprite.
 * @param dest_rect The SDL_Rect defining where to draw the Sprite
 * onscreen.
 * @param tex A pointer to an Texture holding the image data to draw.
 */
Sprite::Sprite(SDL_Rect src_rect, SDL_Rect dest_rect, Texture *tex) {
    this->tex = tex;
    this->src_rect = new SDL_Rect();
    *this->src_rect = src_rect;
    this->dest_rect = new SDL_Rect();
    *this->dest_rect = dest_rect;
    x = dest_rect.x;
    y = dest_rect.y;
}

/**
 * This constructor should be used when either the Sprite should take
 * up the whole screen or the whole texture.
 *
 * @param rect The SDL_Rect either defining what subsection of tex to
 * use as this Sprite or where to draw the Sprite onscreen, depending
 * on dest.
 * @param tex A pointer to an Texture holding the image data to draw.
 * @param dest True if the passed rect shows where to draw the Sprite, false
 * if it shows where the Sprite comes from.
 */
Sprite::Sprite(SDL_Rect rect, Texture *tex, bool dest) {
    SDL_Rect **target_rect;
    SDL_Rect **other_rect;

    this->tex = tex;

    if (dest) {
        target_rect = &dest_rect;
        other_rect = &src_rect;
        x = rect.x;
        y = rect.y;
    } else {
        target_rect = &src_rect;
        other_rect = &dest_rect;
        x = 0;
        y = 0;
    }

    *target_rect = new SDL_Rect();
    **target_rect = rect;
    *other_rect = NULL;
}

/**
 * This constructor should be used when the whole image file should be used,
 * and the Sprite should take up the whole screen.
 *
 * @param tex A pointer to an Texture holding the image data to draw.
 */
Sprite::Sprite(Texture *tex) {
    this->tex = tex;
    src_rect = NULL;
    dest_rect = NULL;
    x = 0;
    y = 0;
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
}

double Sprite::get_draw_x()
{
    return x;
}

double Sprite::get_draw_y()
{
    return y;
}

double Sprite::get_width() {
    if (dest_rect != NULL) {
        return dest_rect->w;
    }

    return 0;
}

double Sprite::get_height() {
    if (dest_rect != NULL) {
        return dest_rect->h;
    }

    return 0;
}

void Sprite::set_draw_x(double x)
{
    if (dest_rect == NULL) {
        dest_rect = new SDL_Rect;
    }

    this->x = x;
}

void Sprite::set_draw_y(double y)
{
    if (dest_rect == NULL) {
        dest_rect = new SDL_Rect;
    }

    this->y = y;
}

void Sprite::set_width(double width)
{
    if (dest_rect == NULL) {
        dest_rect = new SDL_Rect;
    }

    dest_rect->w = width;
}

void Sprite::set_height(double height)
{
    if (dest_rect == NULL) {
        dest_rect = new SDL_Rect;
    }

    dest_rect->h = height;
}

/**
 * Draws the Sprite onscreen.
 *
 * @return True if successfully renderer, false otherwise.
 */
bool Sprite::draw(Renderer *rend) {
    if (rend == NULL) {
        return false;
    }

    if (dest_rect != NULL) {
        dest_rect->x = x;
        dest_rect->y = y;
    }

    return tex != NULL && rend->render_copy(tex, src_rect, dest_rect);
}
