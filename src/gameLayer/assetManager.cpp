//
// Created by socks on 8/15/26.
//

#include "assetManager.h"

void AssetManager::loadAll() {
    dirt = LoadTexture(RESOURCES_PATH "textures/dirt.png");
    textures = LoadTexture(RESOURCES_PATH "textures/textures.png");
    frame = LoadTexture(RESOURCES_PATH "textures/frame.png");
    treeTextures = LoadTexture(RESOURCES_PATH "textures/treetextures.png");
}
