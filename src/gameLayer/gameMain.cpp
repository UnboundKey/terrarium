//
// Created by socks on 8/15/26.
//

#include "gameMain.h"

#include <algorithm>
#include <cmath>
#include <fstream>
#include <iosfwd>

#include "assetManager.h"
#include "raylib.h"
#include "gameMap.h"
#include "helpers.h"
#include "imgui.h"
#include "randomStuff.h"
#include "worldGen.h"

struct GameData {
    GameMap gameMap;
    Camera2D camera = {};

} gameData;

AssetManager assetManager;
int selectedBlock;
float cameraSpeed;
bool initGame() {
    assetManager.loadAll();
    gameData.gameMap.create(1000,500);

    generateWorld(gameData.gameMap, 0xbeef);
    //
    // for (int i = 0; i < gameData.gameMap.mapData.capacity(); i++) {
    //  gameData.gameMap.mapData[i].type = getRandomInt(rng, 0, Block::BLOCK_COUNT-1);
    // }


    gameData.camera.target = {0,0};
    gameData.camera.zoom = 100.0f;
    gameData.camera.rotation = 0.0f;
    return true;
}

bool updateGame() {
    float deltaTime = GetFrameTime();

    if (deltaTime > 1.f/5) {
        deltaTime = (1.f/5);
    }

    ClearBackground({99,155,255,255});
    gameData.camera.offset = {GetScreenWidth() /2.0f,GetScreenHeight() /2.0f};

#pragma region Camera Controls
    if (IsKeyDown(KEY_W)) {gameData.camera.target.y -= cameraSpeed * deltaTime;}
    if (IsKeyDown(KEY_S)) {gameData.camera.target.y += cameraSpeed * deltaTime;}
    if (IsKeyDown(KEY_A)) {gameData.camera.target.x -= cameraSpeed * deltaTime;}
    if (IsKeyDown(KEY_D)) {gameData.camera.target.x += cameraSpeed * deltaTime;}
#pragma endregion
    ImGui::Begin("Block Selector");
    ImGui::SliderFloat("Camera Zoom", &gameData.camera.zoom, 10.0f, 150.0f);
    ImGui::SliderFloat("camera_speed", &cameraSpeed, 0.f ,100.f);
    ImGui::SliderInt("Selected Block", &selectedBlock, 0, Block::BLOCK_COUNT -1);
    ImGui::End();

    Vector2 worldPos = GetScreenToWorld2D(GetMousePosition(),gameData.camera);

    int blockX = (int)floor(worldPos.x);
    int blockY = (int)floor(worldPos.y);

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        auto b = gameData.gameMap.getBlockSafe(blockX,blockY);
        if (b) {
        *b = {};
        }
    }
    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        auto b = gameData.gameMap.getBlockSafe(blockX,blockY);
        if (b) {
         b->type = selectedBlock;
        }
    }

#pragma region Camera Rendering
    BeginMode2D(gameData.camera);

    Vector2 topLeftView = GetScreenToWorld2D({0,0},gameData.camera);
    Vector2 bottomRightView = GetScreenToWorld2D({(float)GetScreenWidth(), (float)GetScreenHeight()}, gameData.camera);

    int startXView = (int)floorf(topLeftView.x -1);
    int endXView = (int)floorf(bottomRightView.x +1 );
    int startYView = (int)floorf(topLeftView.y -1);
    int endYView = (int)floorf(bottomRightView.y +1);

    startXView = std::clamp(startXView,0,gameData.gameMap.w-1);
    endXView = std::clamp(endXView,0,gameData.gameMap.w-1);
    startYView = std::clamp(startYView,0,gameData.gameMap.h-1);
    endYView = std::clamp(endYView,0,gameData.gameMap.h-1);

    for (int y = startYView; y <= endYView; y++) {
        for (int x = startXView; x <= endXView; x++) {
            auto &b = gameData.gameMap.getBlockUnsafe(x,y);
            if (b.type != Block::air) {
            DrawTexturePro(assetManager.textures,
        getTextureAtlas(b.type,0,32,32),
        {(float)x,(float)y,1,1},{}, 0.0f, WHITE);
            }
            if (b.type == Block::woodLog) {
                    uint8_t spriteXIndex = 0;
                auto* leftofblock = gameData.gameMap.getBlockSafe(x-1,y);
                auto rightofblock = gameData.gameMap.getBlockSafe(x+1,y);
                auto topblock = gameData.gameMap.getBlockSafe(x,y-1);
                if (leftofblock && topblock && rightofblock) {
                    bool hasLeavesLeft = leftofblock->type == Block::treeLeaves;
                    bool hasLeavesRight = rightofblock->type == Block::treeLeaves;
                    bool hasLeavesTop = topblock->type == Block::treeLeaves;

                    if (hasLeavesLeft && hasLeavesRight && hasLeavesTop) spriteXIndex = 2;
                    else if (hasLeavesLeft && hasLeavesRight) spriteXIndex = 1;
                    else if (hasLeavesLeft) spriteXIndex = 3;
                    else if (hasLeavesRight) spriteXIndex = 4;

                }
                DrawTexturePro(assetManager.treeTextures,
                                getTextureAtlas(spriteXIndex,0,32,32),
                                {(float)x,(float)y,1,1,},{},0.f,WHITE);

            }
        }
    }



    // for (int y =0; y < gameData.gameMap.h; y++) {
    //     for (int x = 0; x < gameData.gameMap.w; x++) {
    //         auto &b = gameData.gameMap.getBlockUnsafe(x,y);
    //         if (b.type != Block::air) {
    //         DrawTexturePro(assetManager.textures,
    //     getTextureAtlas(b.type,0,32,32),
    //     {(float)x,(float)y,1,1},{}, 0.0f, WHITE);
    //         }
    //     }
    // }
#pragma region Debug Cursor Rendering
    DrawTexturePro(assetManager.textures, getTextureAtlas(selectedBlock,0,32,32), {(float)blockX, (float)blockY,1,1},
                   {}, 0,{255,255,255,127});
    DrawTexturePro(assetManager.frame, {0, 0, (float)assetManager.frame.width, (float)assetManager.frame.height}, {(float)blockX, (float)blockY,1,1},
                   {}, 0,WHITE);
#pragma endregion
    EndMode2D();
    DrawFPS(50,50);
#pragma endregion
    return true;
}

void endGame() {
    std::ofstream outFile( RESOURCES_PATH "log.txt");
    outFile << "GAME CLOSED";
    outFile.close();

}