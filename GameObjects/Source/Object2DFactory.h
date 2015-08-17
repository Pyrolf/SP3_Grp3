#pragma once
#include "Factory.h"
#include "Object2D.h"

class Object2DFactory : public Factory
{
public:
	Object2DFactory();
	~Object2DFactory();
	virtual Object2D* GetObject() = 0;
	void IncreaseSize();

protected:
	Object2D** objs;
	Object2D** objEnd;
};

