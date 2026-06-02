#include <raylib.h>
#include <rlgl.h>
#include "Player/player.hpp"

Player player;

int main()
{
    InitWindow(1280, 720, "K4Craft");

    player.Init();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        float dt = GetFrameTime();

        player.Update(dt);

        BeginDrawing();
        ClearBackground(RAYWHITE);

        BeginMode3D(player.cam.cam);

        DrawPlane({0, 0, 0}, {30, 30}, DARKGREEN);

        rlPushMatrix();
        rlTranslatef(player.position.x, player.position.y + 1.0f, player.position.z);

        rlRotatef(player.yaw, 0, 1, 0);

        DrawCube({0, -0.3f, 0}, 1, 1, 1, DARKBLUE);

        rlPopMatrix();

        EndMode3D();

        DrawText(TextFormat("X: %.2f", player.position.x), 10, 10, 20, DARKGRAY);
        DrawText(TextFormat("Y: %.2f", player.position.y), 10, 30, 20, DARKGRAY);
        DrawText(TextFormat("Z: %.2f", player.position.z), 10, 50, 20, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();
}