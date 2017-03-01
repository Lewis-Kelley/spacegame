#ifndef DRAWABLEDECORATOR_H
#define DRAWABLEDECORATOR_H

#include "Movement.hpp"
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
    double get_width() { return inner->get_width(); }
    double get_height() { return inner->get_height(); }
    void set_draw_x(double x) { inner->set_draw_x(x); }
    void set_draw_y(double y) { inner->set_draw_y(y); }
    void set_width(double width) { inner->set_width(width); }
    void set_height(double height) { inner->set_height(height); }
    virtual void move(double dx, double dy) { inner->move(dx, dy); };
    virtual void move(Movement movement) { inner->move(movement); };
    virtual void start_move(double dx, double dy, MovementType type);
    virtual void start_move(Movement *movement, MovementType type);
    virtual void end_move(MovementType type) { inner->end_move(type); }
    virtual bool draw() { return inner->draw(); }
    virtual void update(double delta) { inner->update(delta); }
};

#endif /* DRAWABLEDECORATOR_H */
