#include "Object2D.h"

Object2D::Object2D()
	:
rotationalVelocity(0),
rotationalAcceleration(0),
active(false)
{
}

Object2D::~Object2D()
{
}

void Object2D::UpdatePosition(const double& deltaTime)
{
	position += velocity * deltaTime;
}

void Object2D::UpdateVelocity(const double& deltaTime)
{
	velocity += acceleration * deltaTime;
}