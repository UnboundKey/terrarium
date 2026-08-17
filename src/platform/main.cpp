#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>

#include "gameMain.h"

int main() {
#if  PRODUCTION_BUILD == 1
        SetTraceLogLevel(LOG_NONE);
#endif

    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(1024, 800, "raylib window");
    SetExitKey(KEY_NULL);
    SetTargetFPS(240);

#pragma region imgui
    rlImGuiSetup(true);
    ImGuiIO& io = ImGui::GetIO();
    io.FontGlobalScale = 1.6f;
#pragma endregion

    if (!initGame()) {
        return 0;
    };

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);
        rlImGuiBegin();
        if (!updateGame()) {
            CloseWindow();
        };
#pragma region ImGui
        rlImGuiEnd();
#pragma endregion
        EndDrawing();
    }
#pragma region ImGui
    rlImGuiShutdown();
#pragma endregion
    CloseWindow();
    endGame();
    return 0;
}
