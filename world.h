#ifndef WORLD_H
#define WORLD_H

const int WIDTH = 200;
const int HEIGHT = 200;

enum TileType {
    FLOOR, WALL, BOUNDS
};

/* floor: new Tile(FLOOR, '.', 0)
 * wall: new Tile(WALL, '#', 0)
 */
class Tile {
    public:
        TileType type;
        char glyph;
        int color;
        Tile(TileType type, char glyph, int color);
        Tile();
};

class World {
    public:
        int width;
        int height;
        Tile tiles[WIDTH][HEIGHT];
        Tile tileat(int x, int y);
        char glyphat(int x, int y);
        int colorat(int x, int y);
        World();
};

class WorldBuilder {
    public:
        int width;
        int height;
        Tile tiles[WIDTH][HEIGHT];
        void randomizeTiles();
        void smooth(int times);
        void makeCaves();
        World build();
        WorldBuilder();
};

#endif
