#ifndef DRAWABLE_H
#define DRAWABLE_H

/**
 * An abstract class representing anything that can be drawn onto the
 * screen.
 */
class Drawable {
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

    virtual void move(double dx, double dy);

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
    virtual void update(double delta) { }
};

#endif /* DRAWABLE_H */
