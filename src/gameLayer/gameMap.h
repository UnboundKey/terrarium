//
// Created by socks on 8/15/26.
//

#ifndef MYGAME_GAMEMAP_H
#define MYGAME_GAMEMAP_H
#include <vector>

#include "blocks.h"


struct GameMap {
    int w = 0;
    int h = 0;

    std::vector<Block> mapData;

    void create(int w, int h);

    Block& getBlockUnsafe(int x, int y);
    Block* getBlockSafe(int x, int y);
};

#endif //MYGAME_GAMEMAP_H