#pragma once
#include "Object2dfactory.h"

class Bullet2DFactory : public Object2DFactory
{
public:
	Bullet2DFactory();
	virtual ~Bullet2DFactory();
	virtual Object2D* GetObject();
};