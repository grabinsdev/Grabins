#include "font.h"

Font LoadSans()
{
    Font f = LoadFontEx(
        TextFormat("%sfonts/Comic Sans MS.ttf", GetApplicationDirectory()),
        20,
        nullptr,
        0
    );

 
    return f;
}