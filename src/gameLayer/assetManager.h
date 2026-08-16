//
// Created by socks on 8/15/26.
//

#ifndef MYGAME_ASSETMANAGER_H
#define MYGAME_ASSETMANAGER_H
#include "raylib.h"

struct AssetManager {
    Texture2D dirt = {};
    Texture2D textures = {};
    Texture2D frame = {};
    Texture2D treeTextures = {};

    void loadAll();

};
#endif //MYGAME_ASSETMANAGER_H