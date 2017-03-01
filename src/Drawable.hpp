#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <stdio.h>
#include <map>

#include "Movement.hpp"

/**
 * An abstract class representing anything that can be drawn onto the
 * screen.
 */
class Drawable {
private:
    std::map<MovementType, Movement *> movements;
    typedef std::pair<MovementType, Movement *> movement_pair;
public:
    virtual ~Drawable() {}

    /**
     * @return The x coordinate of where the image is.
     */
    virtual double get_draw_x() = 0;

    /**
     * @return The y coordinate of where the image is.
     */
    virtual double get_draw_y() = 0;

    /**
     * @return The width of this image.
     */
    virtual double get_width() = 0;

    /**
     * @return The height of this image.
     */
    virtual double get_height() = 0;

    /**
     * Set the x coordinate of where the image is.
     *
     * @param x
     */
    virtual void set_draw_x(double x) = 0;

    /**
     * Set the y coordinate of where the image is.
     *
     * @param y
     */
    virtual void set_draw_y(double y) = 0;

    /**
     * Set the width of this image.
     *
     * @param width
     */
    virtual void set_width(double width) = 0;

    /**
     * Set the height of this image.
     *
     * @param height
     */
    virtual void set_height(double height) = 0;

    virtual void move(double dx, double dy);
    virtual void move(Movement movement);

    virtual void start_move(double dx, double dy, MovementType type);
    virtual void start_move(Movement *movement, MovementType type);
    virtual void end_move(MovementType type);

    /**
     * Draws whatever this drawable represents to the screen.
     *
     * @return True if successfully drawn, false if there was an error.
     */
    virtual bool draw() = 0;

    /**
     * To be used for any updates that need to happen upon a tick.
     *
     * @param delta The time since the last update.
     */
    virtual void update(double delta);
};

#endif /* DRAWABLE_H */
