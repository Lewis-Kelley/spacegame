#ifndef DRAWABLEDECORATOR_H
#define DRAWABLEDECORATOR_H

#include "Drawable.hpp"

/**
 * An abstract decorator of Drawable.
 */
class DrawableDecorator : public Drawable {
private:
    Drawable *inner;
public:
    /**
     * Create a new DrawableDecorator decorating the passed Drawable.
     *
     * @param inner The Drawable this object will decorate.
     */
    DrawableDecorator(Drawable *inner) { this->inner = inner; }
    double get_draw_x() { return inner->get_draw_x(); }
    double get_draw_y() { return inner->get_draw_y(); }
    void set_draw_x(double x) { inner->set_draw_x(x); }
    void set_draw_y(double y) { inner->set_draw_y(y); }
    virtual bool draw() { return inner->draw(); }
    virtual void update(double delta) { inner->update(delta); }
};

#endif /* DRAWABLEDECORATOR_H */
