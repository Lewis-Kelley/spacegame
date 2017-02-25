#include "TileMap.hpp"

/**
 * Return a 2D array of the given dimensions of empty Tile's all
 * properly linked together.
 *
 * @param width The number of Tile's in a row.
 * @param height The number of Tile's in a column.
 * @return A width x height array of pointers to linked Tile's.
 */
Tile ***generate_grid(short width, short height) {
    Tile ***map = new Tile**[height];

    for (short i = 0; i < height; i++) {
        map[i] = new Tile*[width];
    }

    map[0][0] = new Tile(0, 0);
    for (short i = 1; i < width; i++) {
        map[0][i] = new Tile(0, i);
        map[0][i]->add_neighbor(WEST, map[0][i - 1]);
    }

    for (short i = 1; i < height; i++) {
        map[i][0] = new Tile(i, 0);
        map[i][0]->add_neighbor(NORTH, map[i - 1][0]);
        for (short j = 1; j < width; j++) {
            map[i][j] = new Tile(j, i);
            map[i][j]->add_neighbor(NORTH, map[i - 1][j]);
            map[i][j]->add_neighbor(WEST, map[i][j - 1]);
        }
    }

    return map;
}
