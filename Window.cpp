#include "Window.h"


void WindowInit(const char* title)
{   
    InitWindow(640, 480, title);
    SetTargetFPS(30);
}