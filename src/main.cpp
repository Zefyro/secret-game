#include <raylib.h>

int main()
{
    InitWindow(1280, 720, "GMTK-2025");

    SetTargetFPS(0);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawFPS(80, 80);

        EndDrawing();
    }
    CloseWindow();

    return 0;
}