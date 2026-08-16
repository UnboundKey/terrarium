//
// Created by socks on 8/15/26.
//

#ifndef MYGAME_BLOCKS_H
#define MYGAME_BLOCKS_H
#include <cstdint>

struct Block {
    enum  {
        air = 0,
        dirt,
        grass,
        stone,
        woodLog,
        treeLeaves,
        BLOCK_COUNT,
    };
    uint16_t type = 0;
};
#endif //MYGAME_BLOCKS_H