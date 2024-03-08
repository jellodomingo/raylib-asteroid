#include <raylib.h>

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "very bad asteroids");
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
    }

    CloseWindow();
    return 0;
}