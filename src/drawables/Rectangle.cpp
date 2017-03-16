#include "Rectangle.hpp"

/**
 * Create a new Rectangle with the given parameters.
 *
 * @param dest_rect Defines the location where this Rectangle will be
 * drawn.
 * @param color A pointer to some changeable color to draw in.
 */
Rectangle::Rectangle(SDL_Rect dest_rect, SDL_Color *color)
    : dest_rect(new SDL_Rect(dest_rect)), color(color)
{
    rect_surf
        = SDL_CreateRGBSurface(0, window::width, window::height,
                               32, 0, 0, 0, 0);
    x = dest_rect.x;
    y = dest_rect.y;
}

Rectangle::~Rectangle()
{
    delete dest_rect;
    SDL_FreeSurface(rect_surf);
}

double Rectangle::get_draw_x()
{
    return x;
}

double Rectangle::get_draw_y()
{
    return y;
}

double Rectangle::get_width()
{
    return dest_rect->w;
}

double Rectangle::get_height()
{
    return dest_rect->h;
}

void Rectangle::set_draw_x(double x)
{
    this->x = x;
}

void Rectangle::set_draw_y(double y)
{
    this->y = y;
}

void Rectangle::set_width(double width)
{
    dest_rect->w = width;
}

void Rectangle::set_height(double height)
{
    dest_rect->h = height;
}

int my_round(double num)
{
    if (num - (int)num < 0.5 - ROUNDOFF) {
        return (int)num;
    } else {
        return (int)num + 1;
    }
}

bool Rectangle::draw(Renderer *rend)
{
    dest_rect->x = my_round(x);
    dest_rect->y = my_round(y);

    rend->fill_rect(dest_rect, color);

    return true;
}
