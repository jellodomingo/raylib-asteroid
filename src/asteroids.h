#pragma once
#include <raylib.h>

enum AsteroidSize
{
    Small,
    Medium,
    Large
};

class Asteroid
{
private:
    Vector2 position;
    Vector2 direction;
    Vector2 debugDirection;
    float rotationSpeed;
    int radius;
    int size;
    int generateRadius();
    Vector2 getRandomDirection();

public:
    Asteroid();
    Asteroid(Vector2 position, float rotationSpeed, int size);
    bool IsInAsteroid(Vector2 position);
    int GetRadius();
    void UpdateAsteroid();
    void DrawAsteroid();
    Vector2 GetPosition();
    void Warp(Vector2 newPosition);
};