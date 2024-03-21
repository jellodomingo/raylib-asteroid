#pragma once
#include <raylib.h>
#include <vector>
#include "ship.h"
#include "asteroids.h"
#include "projectile.h"

#define MAX_LIVES 5
#define PLAYER_BASE_SIZE 20.0f
#define PLAYER_HEIGHT 30.0f

#define MAX_ASTEROID_ROTATION_SPEED 3.0f
#define MIN_ASTEROID_ROTATION_SPEED 0.5f

class Game
{
private:
    int screenWidth;
    int screenHeight;
    int score;
    int lives;
    bool pause;
    bool gameOver;
    Ship *ship;
    std::vector<Asteroid *> asteroids;
    std::vector<Projectile *> projectiles;

public:
    Game();
    Game(int screenWidth, int screenHeight);
    void SpawnAsteroid(Vector2 position);
    void DeleteAsteroid(Vector2 position);
    void WarpAsteroids(Asteroid *asteroid);
    void WarpShip(Ship *ship);
    bool IsProjectileOB(Projectile *projectile);
    void SpawnProjectile(Vector2 position, Vector2 direction);
    void DeleteProjectile(Vector2 position);
    void UpdateGame();
    void DrawGame();
    void ShutDown();
    bool Paused();
    bool GameOver();
    bool NotInSafeZone(Vector2 position);
    void SpawnAsteroidOutsideView();
};