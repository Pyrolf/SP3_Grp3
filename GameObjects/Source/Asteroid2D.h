#pragma once
#include "Object2d.h"
#include "Killable.h"
#include "DamagesThings.h"

class Asteroid2D : public Object2D, public DamagesThings, public Killable
{
public:
	Asteroid2D();
	~Asteroid2D();
	virtual void Update(const double& deltaTime);
	virtual void DoCollisionWith(Object2D* obj);
};

