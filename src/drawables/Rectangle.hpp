#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <SDL2/SDL.h>

#include "../util/Window.hpp"
#include "Drawable.hpp"

/**
 * A Drawable rectangle. Nothing fancy.
 */
class Rectangle : public Drawable {
private:
    double x;
    double y;
    SDL_Surface *rect_surf;
    SDL_Rect *dest_rect;
    SDL_Color *color;
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
    Rectangle(SDL_Rect dest_rect, SDL_Color *color);
    ~Rectangle();
    virtual bool draw(Renderer *rend);
};

#endif /* RECTANGLE_H */
