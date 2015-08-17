#pragma once
#include "Object2d.h"
#include "Killable.h"
#include "SpawnsObjects.h"

class Ship2D : public Object2D, public Killable, public SpawnsObjects
{
public:
	Ship2D(Factory* factory);
	~Ship2D();
	virtual void Update(const double& deltaTime);
	virtual void DoCollisionWith(Object2D* obj);
};

