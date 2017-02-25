#ifndef ENTITY_H
#define ENTITY_H

#include <stdlib.h>
#include <exception>

#include "Drawable.hpp"
#include "TileDrawable.hpp"
#include "Attack.hpp"
#include "Direction.hpp"

class Tile;
class Unit;

/**
 * Represents any entity that can occupy a tile. It may or may not be
 * attackable, mobile, or anything else. All it does is exists in one
 * tile on the board.
 */
class Entity : public Drawable {
private:
    class NoDrawableException : public std::exception {
        virtual const char* what() const throw()
        {
            return "This Entity has no Drawable\n";
        }
    };
protected:
    TileDrawable *image; ///< The image representing this entity or NULL if none
    Tile *occ_tile; ///< The tile this entity occupies
public:
    Entity(Tile *tile);
    Entity(Tile *tile, TileDrawable *img);

    /**
     * Draws this entity on the screen if there is one to be drawn.
     *
     * @return True if successful or there is no image representing
     * this entity. False otherwise.
     */
    bool draw() { return (image == NULL) ? true : image->draw(); }

    virtual void update(double delta) { if (image != NULL) image->update(delta); }

    virtual double get_draw_x();
    virtual double get_draw_y();
    virtual void set_draw_x(double x);
    virtual void set_draw_y(double y);

    /**
     * Creates a new attack object with target as the target of the
     * attack.
     *
     * @param target The targeted unit in the attack.
     * @return A new attack object filled with all the pertinent
     * information about the attack.
     */
    virtual Attack *make_attack(Unit *target) = 0;

    virtual bool move_ent(Direction dir);
};
#include "Tile.hpp"
#include "Unit.hpp"

#endif /* ENTITY_H */
