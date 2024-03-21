#include "game.h"

Game::Game() = default;

Game::Game(int screenWidth, int screenHeight)
{
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
    pause = false;
    gameOver = false;
    lives = MAX_LIVES;
    score = 0;
    ship = new Ship((Vector2){screenWidth / 2, screenHeight / 2}, GRAY, PLAYER_BASE_SIZE, PLAYER_HEIGHT);
    for (int i = 0; i < 15; i++)
    {
        Vector2 spawnPosition = {0, 0};

        while (NotInSafeZone(spawnPosition))
        {
            spawnPosition.x = GetRandomValue(0, screenWidth);
            spawnPosition.y = GetRandomValue(0, screenHeight);
        }
        SpawnAsteroid(spawnPosition);
    }
}

bool Game::NotInSafeZone(Vector2 position)
{
    bool x = (position.x < screenWidth / 2 + 50 && position.x > screenWidth / 2 - 50);
    bool y = (position.y < screenWidth / 2 + 50 && position.y > screenWidth / 2 - 50);
    return (x && y);
}

bool Game::Paused()
{
    return pause;
}

bool Game::GameOver()
{
    return gameOver;
}

void Game::SpawnProjectile(Vector2 position, Vector2 direction)
{
    projectiles.push_back(new Projectile(position, direction));
}

void Game::SpawnAsteroid(Vector2 position)
{
    asteroids.push_back(new Asteroid(position, MIN_ASTEROID_ROTATION_SPEED, GetRandomValue(0, 2)));
}

void Game::SpawnAsteroidOutsideView()
{
    // Get random position outside play area
    Vector2 spawnPosition;
    Asteroid *newAsteroid = new Asteroid(spawnPosition, MIN_ASTEROID_ROTATION_SPEED, GetRandomValue(0, 2));
    int space = newAsteroid->GetRadius();

    int possibleX[2] = {0 - space, screenWidth + space};

    spawnPosition.x = possibleX[GetRandomValue(0, 1)];
    spawnPosition.y = GetRandomValue(0 - space, screenHeight + space);

    newAsteroid->Warp(spawnPosition);

    asteroids.push_back(newAsteroid);
}

void Game::DeleteAsteroid(Vector2 target)
{
    for (int i = 0; i < asteroids.size(); ++i)
    {
        if (asteroids[i]->IsInAsteroid(target))
        {
            delete asteroids[i];
            asteroids.erase(asteroids.begin() + i);
        }
    }
}

void Game::WarpAsteroids(Asteroid *asteroid)
{
    int space = asteroid->GetRadius();
    Vector2 asteroidPosition = asteroid->GetPosition();

    if (asteroidPosition.x < -space)
    {
        asteroidPosition.x = screenWidth + space;
    }
    else if (asteroidPosition.x > screenWidth + space)
    {
        asteroidPosition.x = -space;
    }

    if (asteroidPosition.y < -space)
    {
        asteroidPosition.y = screenHeight + space;
    }
    else if (asteroidPosition.y > screenHeight + space)
    {
        asteroidPosition.y = -space;
    }

    asteroid->Warp(asteroidPosition);
}

void Game::WarpShip(Ship *ship)
{
    int space = 0;
    Vector2 shipPosition = ship->GetPosition();

    if (shipPosition.x < -space)
    {
        shipPosition.x = screenWidth + space;
        ship->Warp(shipPosition);
    }
    else if (shipPosition.x > screenWidth + space)
    {
        shipPosition.x = -space;
        ship->Warp(shipPosition);
    }

    if (shipPosition.y < -space)
    {
        shipPosition.y = screenHeight + space;
        ship->Warp(shipPosition);
    }
    else if (shipPosition.y > screenHeight + space)
    {
        shipPosition.y = -space;
        ship->Warp(shipPosition);
    }
}

// OB - Out of Bounds
bool Game::IsProjectileOB(Projectile *projectile)
{
    Vector2 projectilePosition = projectile->GetPosition();
    return ((projectilePosition.x < 0 || projectilePosition.x > screenWidth) || (projectilePosition.y < 0 || projectilePosition.y > screenHeight));
}

void Game::UpdateGame()
{
    if (IsKeyPressed(KEY_P))
    {
        pause = !pause;
    }

    // DEBUG
    // if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    // {
    //     SpawnAsteroid(GetMousePosition());
    // }

    // if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    // {
    //     DeleteAsteroid(GetMousePosition());
    // }

    if (lives <= 0)
    {
        gameOver = true;
        pause = true;
    }

    if (!pause)
    {
        if (IsKeyPressed(KEY_SPACE))
        {
            SpawnProjectile(ship->GetPosition(), ship->GetNose());
        }

        // Move Projectiles
        for (int j = 0; j < projectiles.size(); ++j)
        {
            projectiles[j]->UpdateProjectile();
            if (IsProjectileOB(projectiles[j]))
            {
                delete projectiles[j];
                projectiles.erase(projectiles.begin() + j);
            }
        }

        // Move Asteroids
        for (int i = 0; i < asteroids.size(); ++i)
        {
            // Check Ship Collision
            Vector3 shipCollision = ship->GetCollider();

            if (CheckCollisionCircles((Vector2){shipCollision.x, shipCollision.y}, shipCollision.z, asteroids[i]->GetPosition(), asteroids[i]->GetRadius()))
            {
                // DrawCircle(asteroids[i]->GetPosition().x, asteroids[i]->GetPosition().y, asteroids[i]->GetRadius(), PINK);
                lives--;
                ship->Warp({screenWidth / 2, screenHeight / 2});

                delete asteroids[i];
                asteroids.erase(asteroids.begin() + i);

                SpawnAsteroidOutsideView();
            }

            asteroids[i]->UpdateAsteroid();
            WarpAsteroids(asteroids[i]);

            // Check Projectile and Asteroid Collision
            for (int j = 0; j < projectiles.size(); ++j)
            {
                if (asteroids[i]->IsInAsteroid(projectiles[j]->GetPosition()))
                {
                    delete asteroids[i];
                    asteroids.erase(asteroids.begin() + i);

                    delete projectiles[j];
                    projectiles.erase(projectiles.begin() + j);

                    SpawnAsteroidOutsideView();

                    score += 100;
                }
            }
        }

        // Move Ship
        WarpShip(ship);
        ship->UpdateShip();
    }
}

void Game::DrawGame()
{
    BeginDrawing();
    ClearBackground(BLACK);

    for (auto a : asteroids)
    {
        a->DrawAsteroid();
    }

    for (auto p : projectiles)
    {
        p->DrawProjectile();
    }

    ship->DrawShip();

    // DrawText(TextFormat("ASTEROIDS: %i", asteroids.size()), 50, 100, 30, WHITE);

    if (!gameOver)
    {
        DrawText(TextFormat("LIVES: %i", lives), 50, 50, 30, WHITE);
        DrawText(TextFormat("SCORE: %i", score), 2 * screenWidth / 3, 50, 30, WHITE);
    }
    else
    {
        DrawText("GAME OVER", screenWidth / 2 - 100, screenHeight / 2 - 30, 30, RED);
        DrawText(TextFormat("FINAL SCORE: %i", score), screenWidth / 2 - 100, screenHeight / 2 + 30, 30, RED);
    }

    EndDrawing();
}

void Game::ShutDown()
{
    for (auto p : projectiles)
    {
        delete p;
    }

    for (auto a : asteroids)
    {
        delete a;
    }
}