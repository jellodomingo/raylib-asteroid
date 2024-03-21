#include <raylib.h>
#include <math.h>
#include "game.h"

int main()
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "very bad asteroids");
    SetTargetFPS(60);

    Game game = Game(screenWidth, screenHeight);

    while (!WindowShouldClose())
    {
        game.UpdateGame();
        game.DrawGame();
    }

    game.ShutDown();

    CloseWindow();
    return 0;
}