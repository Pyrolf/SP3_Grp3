#include "Asteroid2D.h"

Asteroid2D::Asteroid2D()
{
	health = 100;
	velocity.Set(1,1,1);
	damage = 20;
}

Asteroid2D::~Asteroid2D()
{
}

void Asteroid2D::Update(const double& deltaTime)
{
	UpdatePosition(deltaTime);
}

void Asteroid2D::DoCollisionWith(Object2D* obj)
{
	Killable* killable = dynamic_cast<Killable*>(obj);
	if(killable)
	{
		DoDamageTo(killable);
		if(killable->IsDead())
		{
			obj->active = false;
		}
	}
}