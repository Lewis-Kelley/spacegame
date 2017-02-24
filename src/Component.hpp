#ifndef COMPONENT_H
#define COMPONENT_H

enum Component {
    SHIELD = 1,
    ENGINE = 2,
    WEAPON = 4,
    ALL = SHIELD | ENGINE | WEAPON
};

#endif /* COMPONENT_H */
