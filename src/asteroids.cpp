#include "asteroids.h"
#include <raymath.h>

Asteroid::Asteroid() = default;

Asteroid::Asteroid(Vector2 position, float rotationSpeed, int size)
{
    this->position = position;
    this->direction = getRandomDirection();
    this->debugDirection = Vector2Add(position, Vector2Scale(direction, 25.0f));
    this->rotationSpeed = rotationSpeed;
    this->size = size;
    this->radius = generateRadius();
}

int Asteroid::generateRadius()
{
    return size * 15 + 15;
}

int Asteroid::GetRadius()
{
    return radius;
}

Vector2 Asteroid::GetPosition()
{
    return position;
}

void Asteroid::Warp(Vector2 newPosition)
{
    position = newPosition;
}

Vector2 Asteroid::getRandomDirection()
{
    return Vector2Normalize((Vector2){cosf(GetRandomValue(0, 360) * DEG2RAD), sinf(GetRandomValue(0, 360) * DEG2RAD)});
}

bool Asteroid::IsInAsteroid(Vector2 position)
{
    return CheckCollisionPointCircle(position, this->position, radius);
}

void Asteroid::UpdateAsteroid()
{
    position = Vector2Add(position, direction);
}

void Asteroid::DrawAsteroid()
{
    DrawCircle(position.x, position.y, radius, BROWN);
    // DrawLine(position.x, position.y, debugDirection.x, debugDirection.y, BLACK);
    // DrawText(TextFormat("X: %2.2f Y: %2.2f", direction.x, direction.y), position.x, position.y, 5, BLACK);
}
