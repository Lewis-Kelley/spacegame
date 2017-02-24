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
     * Draws whatever this drawable represents to the screen.
     *
     * @return True if successfully drawn, false if there was an error.
     */
    virtual bool draw() = 0;
};

#endif /* DRAWABLE_H */
