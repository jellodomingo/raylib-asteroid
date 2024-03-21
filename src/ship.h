#pragma once
#include <raylib.h>

#define DEFAULT_ROTATION_SPEED 0.1f
#define MAX_SPEED 0.2f
#define DEFAULT_ACCELERATION 0.0005f

class Ship
{
private:
    Vector2 position;
    int base;
    int height;
    Vector2 speed;
    float acceleration;
    float rotationSpeed;
    float rotation;
    Vector3 collider;
    Color color;
    Vector2 nose;
    Vector2 leftWing;
    Vector2 rightWing;
    bool invincible;

public:
    Ship();
    Ship(Vector2 position, Color color, float base, float height);
    Vector2 GetNose();
    Vector2 GetPosition();
    Vector3 GetCollider();
    void Warp(Vector2 position);
    bool IsInvincible();
    void UpdateShip();
    void DrawShip();
};