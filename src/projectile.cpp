#include "projectile.h"
#include <raymath.h>

Projectile::Projectile() = default;

Projectile::Projectile(Vector2 position, Vector2 direction)
{
    this->position = position;
    this->direction = direction;
}

Vector2 Projectile::GetPosition()
{
    return position;
}

void Projectile::UpdateProjectile()
{
    position = Vector2Add(position, Vector2Scale(direction, DEFAULT_PROJECTILE_SPEED));
}

void Projectile::DrawProjectile()
{
    DrawCircle(position.x, position.y, DEFAULT_PROJECTILE_SIZE, WHITE);
}