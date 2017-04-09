#ifndef MOVEMENT_H
#define MOVEMENT_H

/**
 * Holds information about a 2D movement.
 */
struct Movement {
    double dx;  ///< The amount to move in the x direction.
    double dy;  ///< The amount to move in the y direction.

    /**
     * Initialize a new Movement struct with the given parameters.
     *
     * @param dx The amount to move in the x direction.
     * @param dy The amount to move in the y direction.
     */
    Movement(double dx, double dy) : dx(dx), dy(dy) { }
    Movement() : dx(0), dy(0) { }
};

/**
 * Legal types of Movement's.
 */
enum MovementType {
    CAMERA,
    MOVEMENT
};

#endif /* MOVEMENT_H */
