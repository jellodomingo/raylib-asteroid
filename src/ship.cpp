#include "ship.h"
#include <raymath.h>

Ship::Ship() = default;

Ship::Ship(
    Vector2 position,
    Color color,
    float base,
    float height)
{
    this->position = position;
    this->base = base;
    this->height = height;
    this->color = color;
    this->acceleration = 0;
    this->rotationSpeed = 0;
    this->collider = (Vector3){position.x, position.y, height / 2.0f};
    this->speed = (Vector2){0, 0};
    this->nose = (Vector2){0 + (2 * height / 3), 0};
    this->leftWing = (Vector2){0 - (height / 3), 0 - (base / 2)};
    this->rightWing = (Vector2){0 - (height / 3), 0 + (base / 2)};
}

void Ship::UpdateShip()
{

    // DEALING WITH SPEED

    if (IsKeyDown(KEY_W))
    {
        if (acceleration <= MAX_SPEED)
            acceleration += DEFAULT_ACCELERATION;

        speed = nose;
    }
    else
    {
        acceleration -= DEFAULT_ACCELERATION;

        if (acceleration < 0)
            acceleration = 0;
    }

    position = Vector2Add(Vector2Scale(speed, acceleration), position);

    // SHIP ROTATION
    if (IsKeyDown(KEY_A))
    {
        rotationSpeed = -DEFAULT_ROTATION_SPEED;
    }
    else if (IsKeyDown(KEY_D))
    {
        rotationSpeed = DEFAULT_ROTATION_SPEED;
    }
    else
    {
        rotationSpeed = 0;
    }

    nose = Vector2Rotate(nose, rotationSpeed);
    leftWing = Vector2Rotate(leftWing, rotationSpeed);
    rightWing = Vector2Rotate(rightWing, rotationSpeed);

    collider = (Vector3){position.x, position.y, (height / 2.0f)};
}

bool Ship::IsInvincible()
{
    return invincible;
}

Vector3 Ship::GetCollider()
{
    return collider;
}

Vector2 Ship::GetNose()
{
    return nose;
}

Vector2 Ship::GetPosition()
{
    return position;
}

void Ship::Warp(Vector2 position)
{
    this->position = position;
    this->speed = {0, 0};
}

void Ship::DrawShip()
{

    // DEBUG
    // DrawCircle(nose.x, nose.y, 5.0f, GREEN);
    // DrawCircle(leftWing.x, leftWing.y, 5.0f, BLUE);
    // DrawCircle(rightWing.x, rightWing.y, 5.0f, PINK);
    // DrawCircle(position.x, position.y, height / 4, PINK);
    DrawTriangle(Vector2Add(position, nose), Vector2Add(position, leftWing), Vector2Add(position, rightWing), color);
    // DrawCircle(position.x, position.y, 5.0f, RED);
    // DrawText(TextFormat("Acceleration: %2.2f", acceleration), 100, 120, 10, WHITE);
}