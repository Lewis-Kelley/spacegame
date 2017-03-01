#include "Tile.hpp"

/**
 * Create a new tile at the given coordinates.
 *
 * @param row The row this Tile occupies
 * @param col The column this Tile occupies
 */
Tile::Tile(short row, short col)
{
    this->row = row;
    this->col = col;

    for (int i = 0; i < 4; i++) {
        neighbors[i] = NULL;
    }

    in_range = false;
}

/**
 * Sets the neighboring Tile in the given Direction.
 *
 * @param dir The Direction in which to add the Tile.
 * @param neighbor The new neighbor for this Tile.
 */
void Tile::set_neighbor(Direction dir, Tile *neighbor)
{
    neighbors[index_value(dir)] = neighbor;
}

/**
 * Sets the neighboring Tile in the given Direction, both for this
 * Tile and the neighbor.
 *
 * @param dir The Direction in which to add the Tile.
 * @param neighbor The new neighbor for this Tile.
 */
void Tile::add_neighbor(Direction dir, Tile *neighbor)
{
    set_neighbor(dir, neighbor);
    // print_dir(dir);
    // printf("V\n");
    // print_dir(opp_dir(dir));
    // printf("\n");
    neighbor->set_neighbor(opp_dir(dir), this);
}

/**
 * Returns the neighboring Tile in the given Direction.
 *
 * @param dir The Direction in which to retrieve the neighbor.
 * @return The neighbor in the given Direction.
 */
Tile *Tile::get_neighbor(Direction dir)
{
    return neighbors[index_value(dir)];
}

/**
 * Adds the given entity to the list of entities in this Tile.
 *
 * @param ent The Entity to add.
 */
void Tile::add_entity(Entity *ent)
{
    occ_ents.push_back(ent);
}

/**
 * Removes the passed entity from the list of entities in this Tile if
 * it exists.
 *
 * @param ent The Entity to remove.
 * @return True if successfully removed, false if the passed Entity
 * was never there.
 */
bool Tile::remove_entity(Entity *ent)
{
    for (int i = 0; i < (int)occ_ents.size(); i++) {
        if (occ_ents.at(i) == ent) {
            occ_ents.erase(occ_ents.begin() + i);
            return true;
        }
    }

    return false;
}

/**
 * Moves the passed Entity to the neighboring Tile in the given
 * direction.
 *
 * @param ent The Entity to move.
 * @param dir The Direction in which to move the Entity.
 * @return True if successfully moved, false if the passed Entity was
 * never there or if there is no neighboring Tile in that direction.
 */
bool Tile::move_entity(Entity *ent, Direction dir)
{
    Tile *neighbor = get_neighbor(dir);
    if (neighbor != NULL && neighbor->accepts_entity(ent) && remove_entity(ent)) {
        neighbor->add_entity(ent);
        return true;
    }

    return false;
}

/**
 * Tests if the passed Entity is allowed to pass through this Tile
 * with regards to the Entity's currently stationed here.
 *
 * @param ent The Entity that is trying to pass through.
 * @return True if ent is allowed to pass through, false if it is stopped.
 */
bool Tile::accepts_entity(Entity *ent)
{
    for (int i = 0; i < (int)occ_ents.size(); i++) {
        if (occ_ents.at(i)->stops_ent(ent)) {
            return false;
        }
    }

    return in_range;
}

void Tile::handle_select_unit_event(SelectUnitEvent *event)
{
    for (int i = 0; i < (int)occ_ents.size(); i++) {
        if (occ_ents.at(i) == event->get_selected()) {
            // The 1+ is for the current Tile so it doesn't take any
            // movement.
            define_range(1 + event->get_selected()->get_move_range());
            return;
        }
    }
}

void Tile::handle_deselect_unit_event(DeselectUnitEvent *event)
{
    in_range = false;
}

void Tile::catch_event(Event *event)
{
    switch (event->get_type()) {
    case Event::SELECT_UNIT:
        handle_select_unit_event((SelectUnitEvent *)event);
        break;
    case Event::DESELECT_UNIT:
        handle_deselect_unit_event((DeselectUnitEvent *)event);
        break;
    default:
        break;
    }
}

/**
 * Recursively define the range that the most recently selected Unit
 * can travel through. Right now, this only subtracts 1 at each step.
 *
 * @param move_range The remaining distance the Unit can travel.
 */
void Tile::define_range(short move_range)
{
    in_range = true;

    if (--move_range > 0) {
        for (int i = 0; i < 4; i++) {
            if (neighbors[i] != NULL) {
                neighbors[i]->define_range(move_range);
            }
        }
    }
}
