#include "Bullet2DFactory.h"
#include "Bullet2D.h"

Bullet2DFactory::Bullet2DFactory()
{
}

Bullet2DFactory::~Bullet2DFactory()
{
}

Object2D* Bullet2DFactory::GetObject()
{
	for(Object2D** it = objs; it != objEnd; ++it)
	{
		if(it == NULL)
		{
			*it = new Bullet2D;
			return *it;
		}

		if(!(*it)->active)
		{
			return *it;
		}
	}

	const unsigned index = objEnd - objs;

	IncreaseSize();
	
	Object2D** objPointer = objs + index;
	*objPointer = new Bullet2D;
	return *objPointer;
	
}