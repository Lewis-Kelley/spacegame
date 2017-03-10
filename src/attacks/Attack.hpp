#ifndef ATTACK_H
#define ATTACK_H

#include "../entities/Component.hpp"

/**
 * Holds all the pertinant information about an attack in a packet
 * that can be easily passed around.
 */
class Attack {
private:
    Component tar_comp; ///< The targeted component
    short distance; ///< The grid distance between attacker and attacked unit
public:
    /**
     * @return The component under attack.
     */
    Component get_targeted_comp() { return tar_comp; }

    /**
     * @return The Manhattan distance between the attacking entity and
     * the targeted unit.
     */
    short get_distance() { return distance; }

    /**
     * Calculates the base damage for this attack. This will be
     * reduced by the attacked unit's defenses before dealt as damage.
     *
     * @return The base damage of this attack.
     */
    virtual short get_base_dmg() = 0;
};

#endif /* ATTACK_H */
