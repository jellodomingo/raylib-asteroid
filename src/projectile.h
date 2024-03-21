#pragma once
#include <raylib.h>

#define DEFAULT_PROJECTILE_SPEED 0.5f
#define DEFAULT_PROJECTILE_SIZE 2.0f

class Projectile
{
private:
    Vector2 position;
    Vector2 direction;
    Vector2 debugDirection;

public:
    Projectile();
    Projectile(Vector2 position, Vector2 direction);
    Vector2 GetPosition();
    void UpdateProjectile();
    void DrawProjectile();
};