#include "world.h"
#include <iostream>
#include <cstdlib>

Tile::Tile() {
    this->type = FLOOR;
    this->glyph = '.';
    this->color = 0;
}

Tile::Tile(TileType type, char glyph, int color) {
    this->type = type;
    this->glyph = glyph;
    this->color = color;
}

World::World() {
    width = WIDTH;
    height = HEIGHT;
}


WorldBuilder::WorldBuilder() {
    width = WIDTH;
    height = HEIGHT;
}

void WorldBuilder::randomizeTiles() {
    for(int x = 0; x < width; x++) {
        for(int y = 0; y < height; y++) {
            tiles[x][y] = (rand() % 10) < 5 ? Tile(FLOOR, '.', 0) :
                Tile(WALL, '#', 0);
        }
    }
}

void WorldBuilder::smooth(int times) {
    Tile* tiles2[width][height];
    for(int time = 0; time < times; time++) {
        for(int x = 0; x < width; x++) {
            for(int y = 0; y < height; y++) {
                int floors = 0;
                int rocks = 0;
                for(int ox = -1; ox < 2; ox++) {
                    for(int oy = -1; oy < 2; oy++) {
                        if(x + ox < 0 || x + ox >= width || y + oy < 0 ||
                                y + oy >= height) {
                            continue;
                        }
                        if(tiles[x + ox][y + oy].type == FLOOR) {
                            floors++;
                        }
                        else {
                            rocks++;
                        }
                    }
                }
                tiles2[x][y] = floors >= rocks ? new Tile(FLOOR, '.', 0) :
                    new Tile(WALL, '#', 0);
            }
        }
        for(int i = 0; i < width; i++) {
            for(int j = 0; j < height; j++) {
                tiles[i][j] = *tiles2[i][j];
                delete tiles2[i][j];
            }
        }
    }
}

void WorldBuilder::makeCaves() {
    randomizeTiles();
    smooth(8);
}

World WorldBuilder::build() {
    World w;
    srand(time(NULL));
    makeCaves();
    for(int i = 0; i < width; i++) {
        for(int j = 0; j < height; j++) {
            w.tiles[i][j] = tiles[i][j];
        }
    }
    return w;
}

// If out of bounds, return a new Tile object with TileType BOUNDS
Tile World::tileat(int x, int y) {
    if(x < 0 || x >= width || y < 0 || y >= height) {
        return Tile(BOUNDS, 'x', 0);
    }
    else {
        return tiles[x][y];
    }
}

char World::glyphat(int x, int y) {
    return tileat(x, y).glyph;
}

int World::colorat(int x, int y) {
    return tileat(x, y).color;
}


