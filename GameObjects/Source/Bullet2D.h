#pragma once
#include "Object2D.h"
#include "DamagesThings.h"

class Bullet2D : public DamagesThings, public Object2D
{
public:
	Bullet2D();
	~Bullet2D();

private:
	virtual void Update(const double& deltaTime);
	virtual void DoCollisionWith(Object2D* obj);
};