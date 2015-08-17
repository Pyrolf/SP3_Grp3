#include "Bullet2D.h"

Bullet2D::Bullet2D()
{
	velocity.Set(-20, 0, 0);
	damage = 20;
}

Bullet2D::~Bullet2D()
{
}

void Bullet2D::Update(const double& deltaTime)
{
	UpdatePosition(deltaTime);
}

void Bullet2D::DoCollisionWith(Object2D* obj)
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