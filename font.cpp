#include "font.h"

Font LoadSans()
{
#ifdef __APPLE__
    const char *fontPath = TextFormat(
        "%s../../../fonts/Comic Sans MS.ttf",
        GetApplicationDirectory()
    );
#else
    const char *fontPath = TextFormat(
        "%sfonts/Comic Sans MS.ttf",
        GetApplicationDirectory()
    );
#endif

    Font f = LoadFontEx(fontPath, 20, nullptr, 0);

 
    return f;
}  