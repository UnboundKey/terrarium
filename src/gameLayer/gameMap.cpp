//
// Created by socks on 8/15/26.
//

#include "gameMap.h"
#include "asserts.h"

void GameMap::create(int w, int h) {
    this->w = w;
    this->h = h;
    mapData.resize(w * h);
    for (auto& i : mapData) {i={};}
}

Block &GameMap::getBlockUnsafe(int x, int y) {
    permaAssertCommentDevelopement(GameMap::mapData.size() == w * h, "Map not initialized");
    permaAssertCommentDevelopement(x >= 0 && y>= 0 && x < w && y < h, "getBlockUnsafe: Out of bounds error");

    return mapData[x + y * w];

}

Block * GameMap::getBlockSafe(int x, int y) {
    permaAssertCommentDevelopement(GameMap::mapData.size() == w * h, "Map not initialized");
    if (x < 0 || y < 0 || x >= w || y >= h) {
        return nullptr;
    }
    return &mapData[x + y * w];
}
