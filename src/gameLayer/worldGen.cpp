//
// Created by socks on 8/16/26.
//

#include "worldGen.h"

#include <random>

#include "randomStuff.h"

void generateWorld(GameMap &gameMap, int seed) {
    std::ranlux24_base rand(seed);
    int pickage[] = {Block::stone, Block::stone, Block::stone, Block::stone,Block::stone, Block::stone, Block::dirt, Block::dirt};
    int airAmount = 50;
    int dirtAmount = 30;
    int stoneAmount = 50;
    int surfaceY = airAmount;
    int maxDirectionKeep = 20;
    int direction = 0;
    for (int x = 0; x < gameMap.w; x++) {
        if (maxDirectionKeep > 0) {
            surfaceY += direction;
            maxDirectionKeep--;
        } else {
            direction = getRandomInt(rand,-2,2);
            maxDirectionKeep = getRandomInt(rand,1,4);
        }

        for (int y = 0; y < gameMap.h; y++) {
        Block b;
            if ((y) <= surfaceY) b.type = Block::air;
            else if ( (y) == surfaceY+1) b.type = Block::grass;
            else if ( (y) <= (surfaceY + dirtAmount)) b.type = Block::dirt;
            else if ( (y) <= (surfaceY + dirtAmount) + 5) b.type = pickage[getRandomInt(rand, 0, 7)];
            else if ( (y) < (surfaceY + dirtAmount + stoneAmount)) b.type = Block::stone;
            else b.type = pickage[getRandomInt(rand, 0, 7)];
        gameMap.getBlockUnsafe(x,y) = b;

        }
    }
}
