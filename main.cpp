//forgot to add this main file lol
#include "Window.h"

int main()
{
    WindowInit("Grabins!");
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("terrible text font lol", 190, 200, 20, LIGHTGRAY);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}