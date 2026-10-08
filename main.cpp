//forgot to add this main file lol
#include "Window.h"
#include "font.h"

int main()
{
    WindowInit("Grabins!");
    Font f = LoadSans();


    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);
        DrawTextEx(f, "Camic Snas MS", {190, 200}, 20, 2, LIGHTGRAY);
        EndDrawing();
    }

    UnloadFont(f);
    CloseWindow();
    return 0;
}